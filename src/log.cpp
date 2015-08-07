/*
 * ==================================================================================
 *
 *       Filename:  log.c
 *
 *    Description:  Writes program messages either to stdio, a logfile, or both.
 *
 *        Created:  03/27/2014 09:39:24 PM
 *
 *         Author:  David Keaton (davek), DavekDOS@gmail.com
 *
 * ==================================================================================
 */

#include "dude.h"
#include "log.h"
#include "options.h"
#include "util.h"

#include <time.h>

#include <apr-1/apr_general.h>
#include <apr-1/apr_strings.h>


int is_logfile_enabled = FALSE;                 /* should we write to a logfile as well? */
FILE *logfile = NULL;                           /* non console output logfile */
time_t ntime;
struct tm *ltime;

/* log level strings */
char *str_log_debug		= "[DBG]: ";
char *str_log_fatal		= "[FTL]: ";
char *str_log_error		= "[ERR]: ";
char *str_log_warn		= "[WRN]: ";
char *str_log_info		= "[NFO]: ";

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  log_init
 *  Description:  Create (or append) data to the logfile given in 'filename'. If none
 *  	is specified, does not open a logfile.
 * =====================================================================================
 */
int log_init(char *filename)
{
	char time_now[MAX_STRING];
	if(filename == NULL) {
		/* no filename given? that's cool, use the default logfile's name */
		if((logfile = fopen(DUDE_CONFIG_FILE, "w")) == NULL) {
			log_print(LOG_ERROR, "Unable to open [%s] as logfile.", filename);
			return E_BADFILE;
		}
	} else {
		/* discard the old logfile, to pave the way for our new one */
		if((logfile = fopen(filename, "w")) == NULL) {
			log_print(LOG_ERROR, "Unable to open [%s] as logfile.", filename);
			return E_BADFILE;
		}
	}
	is_logfile_enabled = TRUE;
	time(&ntime);
	ltime = localtime(&ntime);
	strftime(time_now, (MAX_STRING - 1), "[%m.%e.%Y @ %H:%M:%S]", ltime);
	fprintf(logfile, "|>[DUDE]<| log initialized [%s]\n", time_now);
	return E_SUCCESS;
}		/* -----  end of function log_init  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  log_close
 *  Description:  Closes the log file, and replaces what was the fd with NULL.
 * =====================================================================================
 */
int log_close(void)
{
	if(logfile) {
		fclose(logfile);
		logfile = NULL;
		is_logfile_enabled = FALSE;
	}
	return E_SUCCESS;
}		/* -----  end of function log_close  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  log_print
 *  Description:  Prints a message to the log, with a certain log_level. Returns
 *  	an error code on error, or E_SUCCESS if successful.
 * =====================================================================================
 */
int log_print(log_level_e log_level, char *fmt, ...)
{
    va_list vl;                                 /* var args list */
    FILE *f;                                    /* console output handle */
    char *p;                                    /* points to log level string */
    char str_level[MAX_STRING];                 /* intermediary string that prepends LOG_LEVEL string to format string */
    char str_log[MAX_STRING];                   /* log string that's outputted */
    int len;                                    /* length of the buffer left for writing */
	va_start(vl, fmt);
	f = NULL;
	switch(log_level) {
		case LOG_DEBUG:
			/* only display debug info if asked or a define is set */
			f = (debug_mode == TRUE) ? stdout : NULL;
			p = str_log_debug;
			break;
		case LOG_FATAL:
			/* always display fatal errors */
			f = stderr;
			p = str_log_fatal;
			break;
		case LOG_ERROR:
			/* always display critical errors */
			f = stderr;
			p = str_log_error;
			break;
		case LOG_WARN:
			/* show these warnings normally, unless 'quiet' is set (debug_mode overrides) */
			f = (debug_mode == FALSE || settings.silent == TRUE) ? NULL : stderr;
			p = str_log_warn;
			break;
		case LOG_INFO:
			/* show these only if verbose or debug_mode is set */
			f = (debug_mode == TRUE || settings.verbose == TRUE) ? stdout : NULL;
			p = str_log_info;
			break;
		default:
			return E_BADARG;
	}
	/* if there is nowhere we can write, don't bother */
	if(f == NULL && (is_logfile_enabled == FALSE || logfile == NULL)) {
		return E_NOFILE;
	}
	/* set up our format string */
	len = (MAX_STRING - (strlen(fmt) + strlen(p)));
	if(len <= 0) {
		/* overflow detected */
		log_print(LOG_WARN, "buffer overflow: log_print dest=[0x%08X/%db] <- src=[0x%08X/%db]",
				str_level, MAX_STRING, fmt, (strlen(fmt) + len));
		return E_BADLENGTH;
	}
	strncpy(str_level, p, MAX_STRING);
	strcat(str_level, fmt);
//	strncpy(str_level, p, len);
//	strncpy((str_level + len), fmt, strlen(fmt));
//	len = (MAX_STRING - (strlen(fmt) + len));
	/* throw in our varargs */
	vsnprintf(str_log, len, str_level, vl);
	/* add new line to end of buffer */
	str_log[strlen(str_log) - 1] = '\n';
	/* write to console output only if we qualified */
	if(f != NULL) {
		fprintf(f, "%s\n", str_log);
	}
	/* write to the log regardless of qualifiers, only if we are to do so */
	if(is_logfile_enabled == TRUE && logfile != NULL) {
		fprintf(logfile, "%s\n", str_log);
	}
	va_end(vl);
	return E_SUCCESS;
}		/* -----  end of function log_print  ----- */





/* vim: set sw=4 ts=4 sts=4 ft=cpp expandtab: */

