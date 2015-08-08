#ifndef  STRUCTS_INC
#define  STRUCTS_INC

#include "const.h"
#if defined(SDL)
#include <SDL2/SDL.h>
#endif


/* log_level_e
 * Determines the level of logging that takes place, based on how
 * important the information is.
 */
typedef enum {
    LOG_DEBUG,                                  /* debugging information (calls with arguments, return values) */
    LOG_INFO,                                   /* non-error information ('loaded doom2.wad as main iwad') */
    LOG_WARN,                                   /* non-critical errors ('exporting map before building nodes and rejects') */
    LOG_ERROR,                                  /* critical errors ('unable to load WAD, does not exist') */
    LOG_FATAL                                   /* fatal errors ('unable to allocate memory for internal structures') */
} log_level_e;
/* ----------  end of enum log_level_e  ---------- */

/* editor_function_e
 * Defines editor functions, to use in a key array to determine
 * what routine needs to be done for said key.
 */
typedef enum {
    /* movement and zooming */
    EF_VIEWPORT							= 0x1000,
    EF_VIEWPORT_LEFT,                           /* move the editor's view left */
    EF_VIEWPORT_RIGHT,                          /* move the editor's view right */
    EF_VIEWPORT_UP,                             /* move the editor's view up */
    EF_VIEWPORT_DOWN,                           /* move the editor's view down */
    EF_VIEWPORT_ZOOM_IN,                        /* zoom in the grid scale (show more detail) */
    EF_VIEWPORT_ZOOM_OUT,                       /* zoom out the grid scale (show more map) */
    EF_VIEWPORT_ZOOM_DEFAULT,                   /* set the zoom back to the configured default */
    /* object manipulation */
    EF_OBJECT							= 0x2000,
    EF_OBJECT_INSERT,                           /* insert an object under the cursor (or merge objects) */
    EF_OBJECT_DELETE,                           /* delete the selected objects/object under cursor */
    EF_OBJECT_CUT,                              /* delete the object and store in temp reg */
    EF_OBJECT_COPY,                             /* copy the object in temp reg */
    EF_OBJECT_PASTE,                            /* place the object in the temp reg, under the cursor */
    /* main program functions */
    EF_PROGRAM							= 0xF000,
    EF_PROGRAM_SAVE_SETTINGS,                   /* save the changes to the settings */
    EF_PROGRAM_QUIT,                            /* quit the program! */
    EF_NULL                                     /* sentinel */
} editor_function_e;
/* ----------  end of enum editor_function_e  ---------- */

typedef enum {
    MODE_CHOICE,                                /* where the user chooses the wad/pwad */
    MODE_PREVIEW,                               /* shows a preview of the map */
    MODE_EDITOR,                                /* map editor mode */
} dude_mode_e;
/* ----------  end of enum dude_mode_e  ---------- */

/* text_align_e
 * How to determine what sort of text alignment is to occur.
 */
typedef enum {
    TEXT_ALIGN_LEFT,
    TEXT_ALIGN_CENTER,
    TEXT_ALIGN_RIGHT
} text_align_e;
/* ----------  end of enum text_align_e  ---------- */

/* option_type_e
 * Used for the determining the type of option it is, as well
 * as where the option came from.
 */
typedef enum {
    /* what kind of option is it? */
    OPT_ERROR,
    OPT_NONE,
    OPT_STRING,
    OPT_PATH,                                   /* directory/file path (is an array) */
    OPT_INTEGER,
    OPT_BOOLEAN,
    OPT_KEY,                                    /* keyboard keys for customization */
    OPT_ARRAY,                                  /* array of strings */
    OPT_NUMLIST,                                /* list of numbers */
    OPT_CUSTOM,                                 /* custom option, like for extensions (that don't have a set name) */
    OPT_START,
    OPT_END
} option_type_e;
/* ----------  end of enum option_type_e  ---------- */

typedef enum {
    /* where did it come from? */
    FROM_NULL           = 0,                    /* if where it's from doesn't matter (get functions) */
    FROM_DEFAULT        = 1,                    /* default setting */
    FROM_CONFIG         = 2,                    /* config setting */
    FROM_ARGUMENT       = 3,                    /* argument setting */
    FROM_EDITOR         = 4,                    /* set during the runtime of the program, this overrides all others */
    FROM_OVERRIDE       = 9                     /* override any prior argument for whatever reason */
} option_from_e;
/* ----------  end of enum option_from_e  ---------- */

/* element_type_e
 * The type of element of a settings substruct.
 */
typedef enum {
    ET_FROM,
    ET_TYPE,
    ET_IS_CLI_ARG,
    ET_NAME,
    ET_OPTCH,
    ET_HAS_ARG,
    ET_DESCRIPTION,
    ET_VALUE
} element_type_e;
/* ----------  end of enum element_type_e  ---------- */

/* element_access_e
 * How 'access_setting_element' behaves to said element.
 */
typedef enum {
    EA_READ,
    EA_WRITE
} element_access_e;
/* ----------  end of enum element_access_e  ---------- */

/* setting_t
 * Contains the generic setting attributes that are shared
 * by every element.
 */
typedef struct {
    option_from_e from;
    option_type_e type;
    int is_cli_arg;                             /* is this a command line argument? */
    const char *name;                           /* longname of the argument */
    int optch;                                  /* shortname of the argument */
    int has_arg;                                /* has an argument? */
    const char *description;                    /* description of the argument */
} setting_t;
/* ----------  end of struct setting_t  ---------- */

typedef struct {
    setting_t info;
    char *value;
} setting_string_t;
/* ----------  end of struct setting_string_t  ---------- */
//TODO: Determine if a simple typedef is how we want to go with 'setting_path_t'
typedef setting_string_t setting_none_t;
typedef setting_string_t setting_sentinel_t;
typedef setting_string_t setting_path_t;

typedef struct {
    setting_t info;
    apr_int64_t value;
} setting_integer_t;
/* ----------  end of struct setting_integer_t  ---------- */
typedef setting_integer_t setting_boolean_t;

/* key_t
 * contains 'key' and 'mod' elements that represent
 * the modifier key (shift, alt, etc) and keypress
 * ('k', '0', Return, etc), and what function this
 * combination does (insert an object, zoom the map
 * out, etc).
 */
typedef struct {
    editor_function_e func;                     /* what function does this key do? */
    apr_int32_t mod;                            /* what modifier to press (use KEY_NONE for none)) */
    apr_int32_t key;                            /* the key to use (case insensitive) */
} keybinding_t;
/* ----------  end of struct key_t  ---------- */

typedef struct {
    setting_t info;
    keybinding_t value;
} setting_key_t;
/* ----------  end of struct setting_key_t  ---------- */

typedef struct {
    setting_t info;
    apr_array_header_t *value;
} setting_array_t;
/* ----------  end of struct setting_array_t  ---------- */

typedef struct {
    setting_t info;
    int *value;
} setting_numlist_t;
/* ----------  end of struct setting_numlist_t  ---------- */

typedef struct {
    setting_t info;
    char value[MAX_DOOMSTRING];
} setting_doomstr_t;
/* ----------  end of struct setting_doomstring_t  ---------- */

/* ini_section_t
 * Black magic structure to point to each section's
 * corresponding substruct.
 */
typedef struct {
    const char *name;                           /* name of the section */
    void *addr;                                 /* address of the substruct */
} ini_section_t;
/* ----------  end of struct ini_section_t  ---------- */

/* settings_t
 * Is used to typecast an array of setting_t to get the
 * specific name of the option. Merely a convenience
 * structure.
 */
typedef struct {
    int registered;                             /* whether the game is registered or not */
    /* ---------------- */
    /* section   'main' */
    /* ---------------- */
    setting_sentinel_t start;                   /* start sentinel for automated parsing options */
    setting_boolean_t verbose;              	/* should we be verbose? */
    setting_boolean_t quiet;                	/* should we be quiet? */
    setting_boolean_t debug;                	/* print debugging information? */
    setting_path_t config;                  	/* path to another config file */
    setting_path_t logfile;                 	/* path to the logfile, or stderr if null */
    setting_path_t iwad_dir;                	/* IWAD directory */
    setting_path_t iwad;                    	/* IWAD to load as default */
    setting_path_t pwad_dir;                	/* PWAD directory */
    setting_array_t pwad;                    	/* PWAD to load as default */
//TODO: Fill in more!
    setting_none_t help;                  		/* usage */
    setting_none_t version;               		/* version info */
    /* ---------------- */
    /* section 'editor' */
    /* ---------------- */
    /* grid settings */
    setting_integer_t grid_scale;               /* grid zoom level on startup */
    setting_integer_t grid_minimum;             /* smallest size of the grid scale */
    setting_integer_t grid_maximum;             /* largest size of the grid scale */
    setting_boolean_t grid_dashed;              /* whether the grid is displayed as a dash or a line */
    setting_boolean_t grid_hide;                /* whether the grid is shown or not */
    /* sector settings */
    setting_integer_t ceiling_height;           /* height of a ceiling on sector creation */
    setting_integer_t floor_height;             /* height of a floor on sector creation */
    setting_integer_t lighting;                 /* default sector lighting */
    setting_boolean_t increment_sector_tag;		/* should we auto increment the sector tag? */
    /* input settings */
    setting_integer_t scroll_factor;            /* how far a mouse scroll will move the editor */
    /* show something settings */
    setting_boolean_t show_info;                /* show information about the objects in the editor */
    setting_boolean_t show_extended_info;       /* show extended information about the objects in the editor */
    setting_boolean_t show_map_preview;         /* should we show a small preview of the map while browsing the patch wad? */
    setting_boolean_t show_distance;            /* whether we should calculate the distance between two objects and display it */
    setting_boolean_t show_textures;            /* whether we should fill in the sector with its ground texture */
    setting_boolean_t show_things;              /* whether things are shown in the editor or hidden */
    /* editor settings */
    setting_integer_t expert_mode;              /* whether we should ask for overwrite confirmation */
    setting_boolean_t copy_sidedefs;            /* whether the attributes of the prior sidedef are carried to a new one */
    setting_boolean_t special_effects;          /* whether the errors used by special effects are shown or not */
    /* default texture names */
    setting_doomstr_t wall_texture;
    setting_doomstr_t upper_texture;
    setting_doomstr_t lower_texture;
    setting_doomstr_t floor_texture;
    setting_doomstr_t ceiling_texture;
    setting_doomstr_t doortrack_texture;
    setting_doomstr_t door_texture;
    setting_doomstr_t upper_step_texture;
    setting_doomstr_t lower_step_texture;
    setting_doomstr_t teleport_texture;
    /* ---------------- */
    /* section   'keys' */
    /* ---------------- */
    struct {
        setting_key_t object_insert;			/* insert an object under the cursor */
        setting_key_t program_quit;				/* quit DUDE */
    } keymap;
    setting_path_t *extensions;
    ini_section_t sections[SUBSTRUCT_COUNT];    /* contains section names and addr, initialize with static value */
    setting_sentinel_t end;                     /* delimits the end of the automated parsing options */
} settings_t;
/* ----------  end of struct settings_t  ---------- */

/* mp_t
 * Stores APR memory pools for the session.
 */
typedef struct {
    apr_pool_t *root;
    apr_pool_t *file;
    apr_pool_t *config;
    apr_pool_t *strings;
} mp_t;
/* ----------  end of struct mp_t  ---------- */

/* dude_t
 * Main structure, to house most important global objects
 */
typedef struct {
    mp_t mp;                                    /* how can I hold all these pools? */
    dude_mode_e mode;                           /* what mode of the program are we currently in? */
    char *quotes[MAX_QUOTES];                   /* quotes for the version screen */
} dude_t;
/* ----------  end of struct dude_t  ---------- */
#endif   /* ----- #ifndef STRUCTS_INC  ----- */
/* vim: set sw=4 ts=4 sts=4 ft=cpp expandtab: */

