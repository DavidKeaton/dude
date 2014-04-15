/*
 * =====================================================================================
 *
 *       Filename:  dude.c
 *
 *    Description:  David's Unreal Doom Editor
 *
 *        Created:  04/13/2014 12:00:35 PM
 *
 *         Author:  David Keaton (davek), DavekDOS@gmail.com
 *
 * =====================================================================================
 */

#include "dude.h"
#include "logo.h"
#include "log.h"
#include "util.h"

/*-----------------------------------------------------------------------------
 *  variable initialization
 *-----------------------------------------------------------------------------*/
/* quotes to display on version string */
char *quotes[] = {
		"[`Why are you sitting here trying to make a crappy map? Get to playing DOOM!']",
		"[`DUDE may cause a alcoholism. Ask a doctor if DUDE is right for you.']",
		"[`DUDE, coming to a bargain bin near you.']",
		"[`There's a dimensional shambler waiting for you around that Linux shell!']",
		"[`The raddest DOOM editor on the block!']",
		"[`That's one DUUUUUUUDE space marine.']",
		"[`Out of ammo? Time to punch some buns!']"
};

/*-----------------------------------------------------------------------------
 *  forward declarations
 *-----------------------------------------------------------------------------*/
int parse_args(int argc, char **argv);
int parse_config(const char *filename);
int print_usage(void);
int print_version(void);


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  Entrypoint into program.
 * =====================================================================================
 */
int main(int argc, char **argv)
{
	exit(0);
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  print_usage
 *  Description:  Print the command line usage information, as well as version info.
 * =====================================================================================
 */
//int print_usage(void)
//{
//	char *arg_type;
//	fprintf(stdout, DUDE_VERSION_FMT, DUDE_VERSION_STRING, __DATE__, __TIME__);
//	fprintf(stdout, "Options:\n");
//	for(int i = 0; opt_option[i].name != NULL; i++) {
//		if(opt_option[i].has_arg == TRUE) {
//			switch(opt_option[i].optch) {
//				case 'c':
//				case 'l':
//					arg_type = "file";
//					break;
//				case 'id':
//				case 'pd':
//					arg_type = "path[s]";
//					break;
//				case 'iw':
//					arg_type = "IWAD";
//					break;
//				case 'pw':
//					arg_type = "PWAD";
//					break;
//			}
//			if(opt_option[i].optch > 255) {
//				fprintf(stdout, "  --%s=<%s>\n", opt_option[i].name, arg_type);
//			} else if(opt_option[i].optch < 255 && opt_option[i].optch > 0) {
//				fprintf(stdout, "  -%c,--%s=<%s>\n", opt_option[i].optch, opt_option[i].name, arg_type);
//			}
//			fprintf(stdout, "\t%s\n", opt_option[i].description);
//		} else if(opt_option[i].has_arg == FALSE) {
//			if(opt_option[i].optch > 255) {
//				fprintf(stdout, "  --%s\n", opt_option[i].name);
//			} else if(opt_option[i].optch < 255 && opt_option[i].optch > 0) {
//				fprintf(stdout, "  -%c,--%s\n", opt_option[i].optch, opt_option[i].name);
//			}
//			fprintf(stdout, "\t%s\n", opt_option[i].description);
//		}
//	}
//	return E_USAGE;
//}		/* -----  end of function print_usage  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  print_version
 *  Description:  Print version information as well as date & time this program was
 *  	compiled. The format and version string constants are in 'const.h'.
 * =====================================================================================
 */
int print_version(void)
{
    char quote[80];                             /* string to fill with spaces */
	align_text(quote, 80, quotes[rand()%NUM_QUOTES], TEXT_ALIGN_CENTER);
	fprintf(stdout, DUDE_VERSION_FMT, DUDE_VERSION_STRING, __DATE__, __TIME__);
	fprintf(stdout, dude_logo);
	fprintf(stdout, quote);
	fprintf(stdout, "\n");
	return E_USAGE;
}		/* -----  end of function print_version  ----- */




/* vim: set sw=4 ts=4 ft=c: */
