#ifndef  DUDE_INC
#define  DUDE_INC
/*-----------------------------------------------------------------------------
 *  game detection
 *-----------------------------------------------------------------------------*/
/* determine if game is DOOM or HEXEN, default to DOOM */
#if !defined(DOOM) && !defined(HEXEN)
    #define DOOM
#endif
/*-----------------------------------------------------------------------------
 *  DUDE constants
 *-----------------------------------------------------------------------------*/
/* version information */
#define DUDE_VERSION			0x0001
#define DUDE_VERSION_STRING		"0.01"
#define DUDE_VERSION_FMT		\
    "[D]avid's [U]nreal [D]OOM [E]ditor v%s [compiled on %s @ %s]\n"
/* name of the default config file */
#define DUDE_CONFIG_FILE		"dude.ini"
/* how many quotes do we have? */
#define NUM_QUOTES      7       // number of quotes there are
/*-----------------------------------------------------------------------------
 *  platform and support detection
 *-----------------------------------------------------------------------------*/
/* we want our TRUE and FALSE ! */
#if !defined(TRUE) || !defined(FALSE)
    #define TRUE		1
    #define FALSE		0
#endif
/* operating system constants */
#if defined(_WIN32) || defined(__WIN32) || \
    defined(__WIN32__) || defined(_WINNT) || \
    defined(__WINNT__) || defined(__MINGW32__)
    #define OS_WINDOWS
#elif defined(__CYGWIN__)
    #define OS_CYGWIN
#elif defined(unix) || defined(__unix) || defined(__unix__)
    #define OS_UNIX
#elif defined(__linux__)
    #define OS_UNIX
#elif defined(__APPLE__) || defined(__MACH__)
    #define OS_MACOSX
#endif
/* operating system specifics */
#if defined(OS_WINDOWS)
    #include <windef.h>
    #define PATH_DELIMITER	';'
    #define DOOMWADDIR 		"\%DOOMWADDIR\%"
#elif defined(OS_CYGWIN)
    #include <limits.h>
    #define PATH_DELIMITER	':'
    #define DOOMWADDIR 		"$DOOMWADDIR"
#elif defined(OS_UNIX) && !defined(OS_CYGWIN)
    #include <linux/limits.h>
    #define PATH_DELIMITER	':'
    #define DOOMWADDIR 		"$DOOMWADDIR"
#elif defined(OS_MACOSX)
//FIXME: What is the path delimiter on MACOSX? The default DOOM directory?
    #include <limits.h>
    #define PATH_DELIMITER	'?'
    #define DOOMWADDIR 		"$DOOMWADDIR"
#endif
/*-----------------------------------------------------------------------------
 *  game dependent constants
 *-----------------------------------------------------------------------------*/
/* default wad to load */
#if defined(DOOM)
    #define DEFAULT_WAD			"DOOM2.WAD"
    #define DEFAULT_WAD_DIR		DOOMWADDIR
#elif defined(HEXEN)
    #define DEFAULT_WAD			"HEXEN.WAD"
    #define DEFAULT_WAD_DIR		"FILL_ME_IN"
#endif
/*-----------------------------------------------------------------------------
 *  header files
 *-----------------------------------------------------------------------------*/
/* DUDE */
#include "util.h"
/* C */
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <cmath>
/* SDL */
#if defined(SDL)
#include <SDL2/SDL.h>
#endif
/* INIH */
#include <inih/ini.h>
/*-----------------------------------------------------------------------------
 *  constants and defines
 *-----------------------------------------------------------------------------*/
/* error codes */
#define E_UNKNOWN      -1           // unknown error, possible bug 
#define E_USAGE        -2           // error code for when usage is printed, or version info is printed 
#define E_NOMEM        -3           // unable to allocate the necessary memory 
#define E_BADPTR       -4           // bad code pointer 
#define E_BADFILE      -5           // unable to read/write file for whatever reason 
#define E_NOFILE       -6           // unable to find the requested file, as it does not exist 
#define E_BADARG       -7           // program argument error (didn't give an argument a value, etc) 
#define E_BOUNDS       -8           // at some point we overstepped an array 
#define E_CURSES       -9           // ncurses error
#define E_BADSDL       -10          // SDL error 
#define E_BADLENGTH    -11          // bad length or size of data (string, array, etc) 
#define E_KEYUSED      -12          // the key requested has already been bound 
#define E_BADTYPE	   -13		    // bad enumerated/constant type given 
#define E_BADCONFIG    -14          // error parsing the config file 
#define E_OSERROR      -15          // operating system specific error 
/* these two are for inih */
#define E_INIH_ERROR	0
#define E_INIH_SUCCESS	1
/*-----------------------------------------------------------------------------
 *  enumerations
 *-----------------------------------------------------------------------------*/
/** editor_function_e
 * Defines editor functions, to use in a key array to determine
 * what routine needs to be done for said key.
 */
typedef enum {
    /* movement and zooming */
    EF_VIEWPORT							= 0x1000,
    EF_VIEWPORT_LEFT,                   /* move the editor's view left */
    EF_VIEWPORT_RIGHT,                  /* move the editor's view right */
    EF_VIEWPORT_UP,                     /* move the editor's view up */
    EF_VIEWPORT_DOWN,                   /* move the editor's view down */
    EF_VIEWPORT_ZOOM_IN,                /* zoom in the grid scale (show more detail) */
    EF_VIEWPORT_ZOOM_OUT,               /* zoom out the grid scale (show more map) */
    EF_VIEWPORT_ZOOM_DEFAULT,           /* set the zoom back to the configured default */
    /* object manipulation */
    EF_OBJECT							= 0x2000,
    EF_OBJECT_INSERT,                   /* insert an object under the cursor (or merge objects) */
    EF_OBJECT_DELETE,                   /* delete the selected objects/object under cursor */
    EF_OBJECT_CUT,                      /* delete the object and store in temp reg */
    EF_OBJECT_COPY,                     /* copy the object in temp reg */
    EF_OBJECT_PASTE,                    /* place the object in the temp reg, under the cursor */
    /* main program functions */
    EF_PROGRAM							= 0xF000,
    EF_PROGRAM_SAVE_SETTINGS,           /* save the changes to the settings */
    EF_PROGRAM_QUIT,                    /* quit the program! */
    EF_NULL                             /* sentinel */
} editor_function_e;
/* ----------  end of enum editor_function_e  ---------- */

typedef enum {
    MODE_CHOICE,                        /* where the user chooses the wad/pwad */
    MODE_PREVIEW,                       /* shows a preview of the map */
    MODE_EDITOR,                        /* map editor mode */
} dude_mode_e;
/* ----------  end of enum dude_mode_e  ---------- */
/*-----------------------------------------------------------------------------
 *  exports
 *-----------------------------------------------------------------------------*/
/* exported functions */
/* exported variables */
#endif   /* ----- #ifndef DUDE_INC  ----- */
/* vim: set sw=4 ts=4 sts=4 ft=cpp expandtab: */
