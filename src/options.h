/*
 * =====================================================================================
 *
 *       Filename:  options.h
 *
 *    Description:  Contains settings and their defaults.
 *
 *        Created:  04/13/2014 01:16:15 PM
 *
 *         Author:  David Keaton (davek), DavekDOS@gmail.com
 *
 * =====================================================================================
 */

#ifndef  OPTIONS_INC
	#define  OPTIONS_INC
/*-----------------------------------------------------------------------------
 *  preprocessor
 *-----------------------------------------------------------------------------*/
/* option type macros */
#define is_opt_string(x)		(x == OPT_STRING)
#define is_opt_integer(x)		(x == OPT_INTEGER)
#define is_opt_boolean(x)		(x == OPT_BOOLEAN)
#define is_opt_list(x)			(x == OPT_LIST)
/*-----------------------------------------------------------------------------
 *  enumerations
 *-----------------------------------------------------------------------------*/
/* option_type_e
 * Used for the determining the type of option it is.
 */
typedef enum {
	OPT_NONE,
    OPT_STRING,                                 /* (char *) */
    OPT_INTEGER,                                /* (int) */
    OPT_BOOLEAN,                                /* (int) */
    OPT_LIST,                                   /* (void **) */
	OPT_END
} option_type_e;
/* ----------  end of enum option_type_e  ---------- */
/*-----------------------------------------------------------------------------
 *  structures
 *-----------------------------------------------------------------------------*/
/*  */
typedef struct {
    char *shortname;                            /* the short name of the option */
    char *longname;                             /* the long name of the option */
    option_type_e type;                         /* the type of option it is */
    int cli_arg;                                /* TRUE if a command line option */
    int has_arg;                                /* the option has an argument */
    void *where;                                /* where to store the option */
    char *description;                          /* a description of the option */
} option_t;
/* ----------  end of struct option_t  ---------- */

/*  */
typedef struct {
/* ---------------- */
/* section   'main' */
/* ---------------- */
	/* program settings */
    char *config;                               /* path to another config file */
    char *logfile;                              /* path to the logfile, or stderr if null */
    int verbose;                                /* should we be verbose? */
    int silent;                                 /* should we be quiet? */
    char **wadpath;                             /* paths to search for IWADs and PWADs */
    char *iwad;                                 /* IWAD to load as default */
    char **pwad;                                /* PWAD to load as default */
    int registered;                             /* whether the game is registered or not */
/* ---------------- */
/* section 'editor' */
/* ---------------- */
	/* grid settings */
    int grid_scale;                             /* grid zoom level on startup */
    int grid_minimum;                           /* smallest size of the grid scale */
    int grid_maximum;                           /* largest size of the grid scale */
    int grid_dashed;                            /* whether the grid is displayed as a dash or a line */
    int grid_hide;                              /* whether the grid is shown or not */
	/* sector settings */
    int ceiling_height;                         /* height of a ceiling on sector creation */
    int floor_height;                           /* height of a floor on sector creation */
    int sector_lighting;                        /* default sector lighting */
    int increment_sector_tag;                   /* should we auto increment the sector tag? */
	/* input settings */
    int scroll_factor;                          /* how far a mouse scroll will move the editor */
	/* show something settings */
    int show_info;                              /* show information about the objects in the editor */
    int show_extended_info;                     /* show extended information about the objects in the editor */
    int show_map_preview;                       /* should we show a small preview of the map while browsing the patch wad? */
    int show_distance;                          /* whether we should calculate the distance between two objects and display it */
    int show_textures;                          /* whether we should fill in the sector with its ground texture */
    int show_things;                            /* whether things are shown in the editor or hidden */
	/* editor settings */
    int expert_mode;                            /* whether we should ask for overwrite confirmation */
    int move_increment;                         /* the amount of cells to move per 'flick' of the mouse or tap of the movement keys */
    int copy_sidedefs;                          /* whether the attributes of the prior sidedef are carried to a new one */
    int special_effects;                        /* whether the errors used by special effects are shown or not */
	/* default texture names */
    char wall_texture[8];                       /* default wall texture */
    char upper_texture[8];                      /* default upper texture */
    char lower_texture[8];                      /* default lower texture */
    char floor_texture[8];                      /* default floor texture */
    char ceiling_texture[8];                    /* default ceiling texture */
    char doortrack_texture[8];                  /* default doortrack texture */
    char door_texture[8];                       /* default door texture */
    char upper_step_texture[8];                 /* default upper texture */
    char lower_step_texture[8];                 /* default lower texture */
    char teleport_texture[8];                   /* default teleporter texture */
/* ---------------- */
/* section   'keys' */
/* ---------------- */
//	struct {
//		object_insert;			/* insert an object under the cursor */
//		program_quit;				/* quit DUDE */
//	} keymap;
    char **extensions;                          /* extensions to the doom editor to load */
//    ini_section_t sections[SUBSTRUCT_COUNT];    /* contains section names and addr, initialize with static value */
} settings_t;
/* ----------  end of struct settings_t  ---------- */
/*-----------------------------------------------------------------------------
 *  exports
 *-----------------------------------------------------------------------------*/
/* variables */
extern int debug_mode;                          /* whether debugging messages will be printed */
extern settings_t settings;
extern option_t options[];
/* functions */
char *get_shortname(char *argument);
char *get_longname(char *argument);
int get_optch(char *shortname);
unsigned int get_index_from_name(char *name);
char *get_value_from_shortname(char *argument);
char *get_value_from_longname(char *argument);
#endif   /* ----- #ifndef OPTIONS_INC  ----- */
/* vim: set sw=4 ts=4 sts=4 ft=cpp expandtab: */
