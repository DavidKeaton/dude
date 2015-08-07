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
#include "options.h"
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
int dude_init(int argc, char **argv);
void dude_close(void);
int parse_args(int argc, char **argv);
int parse_config(const char *filename);
int print_usage(FILE *where);
int print_version(FILE *where);
int print_awesome(FILE *where);


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  Entrypoint into program.
 * =====================================================================================
 */
int main(int argc, char **argv)
{
	dude_init(argc, argv);
	/* exit with no errors */
	exit(0);
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  dude_init
 *  Description:  
 * =====================================================================================
 */
int dude_init(int argc, char **argv)
{
	/* setup 'dude_close' as an exit hook */
	atexit(dude_close);
	/* parse the arguments on the command line */
	parse_args(argc, argv);
	return OK;
}		/* -----  end of function dude_init  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  dude_close
 *  Description:  
 * =====================================================================================
 */
void dude_close(void)
{
	return;
}		/* -----  end of function dude_close  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  parse_args
 *  Description:  
 * =====================================================================================
 */
int parse_args(int argc, char **argv)
{
    char *p_arg, *p_value;                      /* holds argument name and value pointers for tokenization */
	unsigned int index;
	index = get_index_from_name("config");
	/* test for a configuration file passed */
	for(int i = 0; i < (argc - 1); ++i) {
		if(match(get_shortname(argv[i]), options[index].shortname)) {
			parse_config(argv[i + 1]);
		} else if(match(get_longname(argv[i]), options[index].longname)) {
			parse_config(
		}
	}
	/* run down every possible option, so order precedence is followed */
	for(int i = 0; options[i].type != OPT_END; ++i) {
		if(options[i].cli_arg == TRUE) {
			/* make sure we are still under total argument count */
			if(count >= argc) {
				break;
			}
			/* zero our pointers so we can determine errors */
			p_arg = p_value = NULL;
			/* is it --version or --help? */
			if(options[i].type == OPT_NONE) {
				if(match(get_longname(argv[count]), "version")) {
					return print_awesome(stdout);
				} else if(match(get_longname(argv[count]), "help")) {
					return print_usage(stdout);
				}
			/* is it a valid shortname? */
			} else if(match(get_shortname(argv[count]), options[i].shortname)) {
				/* if it is a boolean, we don't need a value */
				if(options[i].type == OPT_BOOLEAN) {
					p_value = "true";
				} else {
					/* make sure an argument follows */
					if(count >= (argc - 1)) {
						/* overflow if argv was accessed */
						return ERR;
					}
					p_arg = (argv[count++] + 1);
					p_value = argv[count++];
				}
			/* or is it a longname? */
			} else if(match(get_longname(argv[count]), options[i].longname)) {
				/* more in depth boolean test for longnames... */
				if(options[i].type == OPT_BOOLEAN) {
					/* determine if false (if '--no-' is present) */
					if(match(argv[count], "--no-")) {
						p_value = "false";
					} else {
						p_value = "true";
					}
				} else {
					/* the argument should be split on the '=' */
					p_arg = ++argv[count++];
					strtok(++p_arg, "=");
					p_value = strtok(NULL, "=");
				}
			} else {
				continue;
			}
			if(!p_arg || !p_value) {
				/* error in parsing name and/or value */
				return ERR;
			}
			/* if config file given, parse it */
			if(match(p_arg, "c") || match(p_arg, "config")) {
				parse_config(p_value);
			}
			/* set the option */
			switch(options[i].type) {
				case OPT_STRING:
					options[i].where = strndup(p_value, MAX_STRING);
					break;
				case OPT_INTEGER:
					*((int *)options[i].where) = atoi(p_value);
					break;
				case OPT_BOOLEAN:
					*((int *)options[i].where) = get_boolean(p_value);
					break;
				case OPT_LIST:
					append_list_item(options[i].where, p_value);
					break;
				/* should not reach this */
				case OPT_NONE:
				default:
					return ERR;
			}
		}
	}
	return OK;
}		/* -----  end of function parse_args  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  parse_config
 *  Description:  
 * =====================================================================================
 */
int parse_config(const char *filename)
{
	return OK;
}		/* -----  end of function parse_config  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  print_usage
 *  Description:  Print the command line usage information, as well as version info.
 * =====================================================================================
 */
int print_usage(FILE *where)
{
	char *fmt_short			= "  -%c,--%s\n";
	char *fmt_long			= "  --%s\n";
	char *fmt_short_arg		= "  -%c,--%s=<%s>\n";
	char *fmt_long_arg		= "  --%s=<%s>\n";
	char *fmt_long_boolean	= "  --[no-]%s\n";
	char *fmt, *fmt_arg1, *fmt_arg2, *fmt_arg3, *value_type;
	print_version(where);
	fprintf(where, "Options:\n");
	for(int i = 0; options[i].type != OPT_END; ++i) {
		/* determine what value type is for this option */
		switch(get_optch(options[i].shortname)) {
			case 'c':
			case 'l':
				value_type = "file";
				break;
			case 'wp':
				value_type = "path";
				break;
			case 'iw':
				value_type = "IWAD";
				break;
			case 'pw':
				value_type = "PWAD";
				break;
		}
		/* determine what type of definition to print */
		fmt = (options[i].has_arg == TRUE)
			? ((is_valid_string(options[i].shortname))	? fmt_short_arg	: fmt_long_arg)
			: ((is_valid_string(options[i].shortname))	? fmt_short		: ((options[i].type == OPT_BOOLEAN)
						? fmt_long_boolean	: fmt_long));
		/* determine the variables to be formatted in */
		fmt_arg1 = (is_valid_string(options[i].shortname))	? options[i].shortname	: options[i].longname;
		fmt_arg2 = (is_valid_string(options[i].shortname))	? options[i].longname	: value_type;
		fmt_arg3 = (is_valid_string(options[i].shortname))	? value_type			: NULL;
		/* print the definition and explanation */
		fprintf(where, fmt, fmt_arg1, fmt_arg2, fmt_arg3);
		fprintf(where, "\t%s\n", options[i].description);
	}
	return E_USAGE;
}		/* -----  end of function print_usage  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  print_version
 *  Description:  Print version information as well as date & time this program was
 *  	compiled. The format and version string constants are in 'const.h'.
 * =====================================================================================
 */
int print_version(FILE *where)
{
	fprintf(where, DUDE_VERSION_FMT, DUDE_VERSION_STRING, __DATE__, __TIME__);
	return E_USAGE;
}		/* -----  end of function print_version  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  print_awesome
 *  Description:  
 * =====================================================================================
 */
int print_awesome(FILE *where)
{
    char quote[80];                             /* string to fill with spaces */
	align_text(quote, 80, quotes[rand()%NUM_QUOTES], TEXT_ALIGN_CENTER);
	print_version(where);
	fprintf(where, dude_logo);
	fprintf(where, quote);
	fprintf(where, "\n");
	return E_USAGE;
}		/* -----  end of function print_awesome  ----- */



/* vim: set sw=4 ts=4 sts=4 ft=cpp expandtab: */
