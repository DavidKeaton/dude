/*
 * =====================================================================================
 *
 *       Filename:  options.c
 *
 *    Description:  Contains settings and their defaults.
 *
 *        Created:  04/13/2014 01:16:03 PM
 *
 *         Author:  David Keaton (davek), DavekDOS@gmail.com
 *
 * =====================================================================================
 */

#include "dude.h"
#include "options.h"


/*-----------------------------------------------------------------------------
 *  enumerations
 *-----------------------------------------------------------------------------*/
/* name_type_e
 * used in 'get_name' to determine if shortname or longname
 * is wanted.
 */
typedef enum {
	TYPE_SHORTNAME,
	TYPE_LONGNAME,
} name_type_e;
/* ----------  end of enum name_type_e  ---------- */

/*-----------------------------------------------------------------------------
 *  variables
 *-----------------------------------------------------------------------------*/
/* should we be printing debugging messages? */
int debug_mode = DEBUG_DEFAULT;
/* to store the default settings for each */
settings_t settings = {
	.config							= DUDE_CONFIG_FILE,
	.logfile						= NULL,
	.verbose						= FALSE,
	.silent							= FALSE,
	.wadpath						= {DEFAULT_WAD_DIR},
	.iwad							= DEFAULT_WAD,
	.pwad							= {NULL},
	.grid_scale						= 8,
	.grid_minimum					= 2,
	.grid_maximum					= 256,
	.grid_dashed					= FALSE,
	.grid_hide						= FALSE,
	.ceiling_height					= 128,
	.floor_height					= 0,
	.sector_lighting				= 255,
	.increment_sector_tag			= TRUE,
	.scroll_factor					= 10,
	.show_info						= TRUE,
	.show_extended_info				= TRUE,
	.show_map_preview				= TRUE,
	.show_distance					= TRUE,
	.show_textures					= TRUE,
	.show_things					= TRUE,
	.expert_mode					= FALSE,
	.move_increment					= 4,
	.copy_sidedefs					= TRUE,
	.special_effects				= FALSE,
	.upper_texture					= "",
	.lower_texture					= "",
	.floor_texture					= "",
	.ceiling_texture				= "",
	.doortrack_texture				= "",
	.door_texture					= "",
	.upper_step_texture				= "",
	.lower_step_texture				= "",
	.teleport_texture				= ""
};

/* option_t options[]
 * To parse the command line options, and display their descriptions.
 */
option_t options[] = {
/*		(names)																	(*_arg)
 * 	short		long									type				cli		has		where,
 *  	description			*/
	{"c",		"config",								OPT_STRING,			TRUE,	TRUE,	&settings.config,
		"alternate configuration file to load"},
	{"l",		"logfile",								OPT_STRING,			TRUE,	TRUE,	&settings.logfile,
		"file to store log messages"},
	{"v",		"verbose",								OPT_BOOLEAN,		TRUE,	FALSE,	&settings.verbose,
		"verbose outuput"},
	{"q",		"silent",								OPT_BOOLEAN,		TRUE,	FALSE,	&settings.silent,
		"silence output"},
	{"wp",		"wadpath",								OPT_LIST,			TRUE,	TRUE,	&settings.wadpath,
		"path[s] to use when searching for wads (may use multiple times)"},
	{"iw",		"iwad",									OPT_STRING,			TRUE,	TRUE,	&settings.iwad,
		"internal wad to load"},
	{"pw",		"pwad",									OPT_LIST,			TRUE,	TRUE,	&settings.pwad,
		"patch wad[s] to load (may use multiple times)"},
	{"h",		"help",									OPT_NONE,			TRUE,	FALSE,	NULL,
		"display this usage screen"},
	{"V",		"version",								OPT_NONE,			TRUE,	FALSE,	NULL,
		"display version information"},
	/* grid settings */
	{"",		"grid_scale",							OPT_INTEGER,		FALSE,	TRUE,	&settings.grid_scale,
		"the scale setting of the grid upon entry to the editor"},
	{"",		"grid_minimum",							OPT_INTEGER,		FALSE,	TRUE,	&settings.grid_minimum,
		"the largest the grid can zoom"},
	{"",		"grid_maximum",							OPT_INTEGER,		FALSE,	TRUE,	&settings.grid_maximum,
		"the smallest the grid can zoom"},
	{"",		"grid_dashed",							OPT_BOOLEAN,		FALSE,	TRUE,	&settings.grid_dashed,
		"whether the grid lines are dashed or full"},
	{"",		"grid_hide",							OPT_BOOLEAN,		FALSE,	TRUE,	&settings.grid_hide,
		"whether to display the grid or not"},
	/* sector settings */
	{"",		"default_ceiling_height",				OPT_BOOLEAN,		FALSE,	TRUE,	&settings.ceiling_height,
		"default ceiling height for new sectors"},
	{"",		"default_floor_height",					OPT_INTEGER,		FALSE,	TRUE,	&settings.floor_height,
		"default floor height for new sectors"},
	{"",		"default_sector_lighting",				OPT_INTEGER,		FALSE,	TRUE,	&settings.sector_lighting,
		"default lighting amount for new sectors"},
	{"",		"increment_sector_tag",					OPT_INTEGER,		FALSE,	TRUE,	&settings.increment_sector_tag,
		"whether sector tags should auto-increment, or remain manually updated"},
	/* input settings */
	{"",		"scroll_factor",						OPT_INTEGER,		FALSE,	TRUE,	&settings.scroll_factor,
		"how fast the editor scrolls on mouse tap to the screen"},
	{"",		"show_info",							OPT_INTEGER,		FALSE,	TRUE,	&settings.show_info,
		"show information about map object[s]"},
	/* show something settings */
	{"",		"show_extended_info",					OPT_BOOLEAN,		FALSE,	TRUE,	&settings.show_extended_info,
		"show extended information about map object[s]"},
	{"",		"show_map_preview",						OPT_BOOLEAN,		FALSE,	TRUE,	&settings.show_map_preview,
		"show map preview selection screen"},
	{"",		"show_distance",						OPT_BOOLEAN,		FALSE,	TRUE,	&settings.show_distance,
		""},
	{"",		"show_textures",						OPT_BOOLEAN,		FALSE,	TRUE,	&settings.show_textures,
		""},
	{"",		"show_things",							OPT_BOOLEAN,		FALSE,	TRUE,	&settings.show_things,
		""},
	/* editor settings */
	{"",		"expert_mode",							OPT_BOOLEAN,		FALSE,	TRUE,	&settings.expert_mode,
		""},
	{"",		"move_increment",						OPT_INTEGER,		FALSE,	TRUE,	&settings.move_increment,
		""},
	{"",		"copy_sidedefs",						OPT_BOOLEAN,		FALSE,	TRUE,	&settings.copy_sidedefs,
		""},
	{"",		"special_effects",						OPT_BOOLEAN,		FALSE,	TRUE,	&settings.special_effects,
		""},
	/* default texture names */
	{"",		"default_wall_texture",					OPT_BOOLEAN,		FALSE,	TRUE,	&settings.wall_texture,
		""},
	{"",		"default_upper_texture",				OPT_STRING,			FALSE,	TRUE,	&settings.upper_texture,
		""},
	{"",		"default_lower_texture",				OPT_STRING,			FALSE,	TRUE,	&settings.lower_texture,
		""},
	{"",		"default_floor_texture",				OPT_STRING,			FALSE,	TRUE,	&settings.floor_texture,
		""},
	{"",		"default_ceiling_texture",				OPT_STRING,			FALSE,	TRUE,	&settings.ceiling_texture,
		""},
	{"",		"default_doortrack_texture",			OPT_STRING,			FALSE,	TRUE,	&settings.doortrack_texture,
		""},
	{"",		"default_door_texture",					OPT_STRING,			FALSE,	TRUE,	&settings.door_texture,
		""},
	{"",		"default_upper_step_texture",			OPT_STRING,			FALSE,	TRUE,	&settings.upper_step_texture,
		""},
	{"",		"default_lower_step_texture",			OPT_STRING,			FALSE,	TRUE,	&settings.lower_step_texture,
		""},
	{"",		"default_teleport_texture",				OPT_STRING,			FALSE,	TRUE,	&settings.teleport_texture,
		""},
	{NULL, 		NULL, 									OPT_END, 			0, 		0, 		NULL, NULL}
//	{"",		"",							OPT_,			TRUE,	0,	&settings.,
//		""},
//	{"",		"",							OPT_,			TRUE,	0,	&settings.,
//		""},
};
/*-----------------------------------------------------------------------------
 *  functions
 *-----------------------------------------------------------------------------*/
char *get_name(char *argument, name_type_e type);
char *get_value_from_name(char *argument, name_type_e type);

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  get_name
 *  Description:  get_(short|long)name funnels into this function, to optimize.
 *
 * 	Returns:
 * 		(See get_shortname or get_longname)
 * =====================================================================================
 */
char *get_name(char *argument, name_type_e type)
{
	/* validate characters */
	if(*argument == '-') {
		switch(type) {
			case TYPE_SHORTNAME:
				return (*(argument + 1) != '-') ? (argument + 1) : NULL;
			case TYPE_LONGNAME:
				return (*(argument + 1) == '-') ? (argument + 2) : NULL;
			default:
				break;
		}
	}
	return argument;
}		/* -----  end of function get_name  ----- */
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  get_shortname
 *  Description:  retrieves the short name of the given 'argument', and also checks to
 *  	make sure it is valid by checking for a preceding '-'.
 *
 *	Returns:
 *		argument		= Invalid argument (does not have preceding '-')
 *		[else]			= Pointer to argument shortname (the letter(s) for the argument)
 * =====================================================================================
 */
char *get_shortname(char *argument)
{
	return get_name(argument, TYPE_SHORTNAME);
}		/* -----  end of function get_shortname  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  get_longname
 *  Description:  retrieves the long name of the given 'argument', and also checks to
 *  	make sure it is valid by checking for a preceding '--'.
 *
 *	Returns:
 *		argument		= Invalid argument (does not have preceding '--')
 *		[else]			= Pointer to argument longname (the word(s) for the argument)
 * =====================================================================================
 */
char *get_longname(char *argument)
{
	return get_name(argument, TYPE_LONGNAME);
}		/* -----  end of function get_longname  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  get_optch
 *  Description:  
 *
 *  TODO: Make sure this plays well with various endians!
 * =====================================================================================
 */
int get_optch(char *shortname)
{
    int optch;                                  /* stores the converted value from string to numeric */
	/* only deal with 4 characters, as that is the max optch allowed */
	optch  = ((*shortname++) << 24);
	optch |= ((*shortname++) << 16);
	optch |= ((*shortname++) <<  8);
	optch |= ((*shortname++) <<  0);
	return optch;
}		/* -----  end of function get_optch  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  get_index_from_name
 *  Description:  Searches for, and returns, the pointer to the option 
 * =====================================================================================
 */
unsigned int get_index_from_name(char *name)
{
	for(int i = 0; options[i].type != OPT_END; ++i) {
		/* check shortname */
		if(match(name, options[i].shortname) || match(name, options[i].shortname)) {
			return i;
		}
	}
	return ERR;
}		/* -----  end of function get_index_from_name  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  get_value_from_name
 *  Description:  
 * =====================================================================================
 */
char *get_value_from_name(char *argument, name_type_e type)
{
	unsigned int index;
	char *p_arg, *p_value;
	/* zero our pointers so we can determine errors */
	p_arg = p_value = NULL;
	switch(type) {
		case TYPE_LONGNAME:
			/* determine if we need to evaluate a boolean */
			return (is_opt_boolean(options[get_index_from_name(argument)].type))
				/* check to see if we invert the boolean */
				? ((match(argument, "--no-"))
						? "false"
						: "true")
				: ((strtok(get_longname(argument), "=") != NULL)
						? strtok(NULL, "=")
						: NULL);
//			if(is_opt_boolean(options[index].type)) {
//				/* determine if false (if '--no-' is present) */
//				return (match(argument, "--no-")) ? "false" : "true";
//			} else {
//				/* the argument should be split on the '=' */
//				return (strtok(get_longname(argument), "=") != NULL) ? strtok(NULL, "=") : NULL;
//			}
			break;
		case TYPE_SHORTNAME:
		default:
			break;
	}
	return NULL;
}		/* -----  end of function get_value_from_name  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  get_value_from_shortname
 *  Description:  
 * =====================================================================================
 */
char *get_value_from_shortname(char *argument)
{
	return get_value_from_name(argument, TYPE_SHORTNAME);
}		/* -----  end of function get_value_from_shortname  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  get_value_from_longname
 *  Description:  
 * =====================================================================================
 */
char *get_value_from_longname(char *argument)
{
	return get_value_from_name(argument, TYPE_LONGNAME);
}		/* -----  end of function get_value_from_longname  ----- */
/* vim: set sw=4 ts=4 ft=c: */
