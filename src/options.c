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
 *  variable initialization
 *-----------------------------------------------------------------------------*/
/* should we be printing debugging messages? */
int debug_mode = DEBUG_DEFAULT;
/* to store the default settings for each */
settings_t settings = {
	.verbose						= FALSE,
	.silent							= FALSE,
	.config							= DUDE_CONFIG_FILE,
	.logfile						= NULL,
	.wadpath						= {"$DOOMWADDIR"},
	.iwad							= "DOOM2.WAD",
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
	{"v",		"verbose",								OPT_BOOLEAN,		TRUE,	FALSE,	&settings.verbose,
		"verbose outuput"},
	{"q",		"silent",								OPT_BOOLEAN,		TRUE,	FALSE,	&settings.silent,
		"silence output"},
	{"c",		"config",								OPT_STRING,			TRUE,	TRUE,	&settings.config,
		"alternate configuration file to load"},
	{"l",		"logfile",								OPT_STRING,			TRUE,	TRUE,	&settings.logfile,
		"file to store log messages"},
	{"wp",		"wadpath",								OPT_STRINGLIST,		TRUE,	TRUE,	&settings.wadpath,
		"path[s] to use when searching for wads (may use multiple times)"},
	{"iw",		"iwad",									OPT_STRING,			TRUE,	TRUE,	&settings.iwad,
		"internal wad to load"},
	{"pw",		"pwad",									OPT_STRINGLIST,		TRUE,	TRUE,	&settings.pwad,
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
};

//	{"",		"",							OPT_,			TRUE,	0,	&settings.,
//		""},
//	{"",		"",							OPT_,			TRUE,	0,	&settings.,
//		""},


/* vim: set sw=4 ts=4 ft=c: */
