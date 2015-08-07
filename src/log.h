/*
 * ==================================================================================
 *
 *       Filename:  log.h
 *
 *    Description:  Writes program messages either to stdio, a logfile, or both.
 *
 *        Created:  03/27/2014 09:39:17 PM
 *
 *         Author:  David Keaton (davek), DavekDOS@gmail.com
 *
 * ==================================================================================
 */

#ifndef  LOG_INC
	#define  LOG_INC
#include "dude.h"

/*-----------------------------------------------------------------------------
 *  enumerations
 *-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 *  exports
 *-----------------------------------------------------------------------------*/
/* function exports */
int log_init(char *filename);
int log_close(void);
int log_print(log_level_e log_level, char *fmt, ...);

#endif   /* ----- #ifndef LOG_INC  ----- */
/* vim: set sw=4 ts=4 sts=4 ft=cpp expandtab: */

