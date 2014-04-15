/*
 * ==================================================================================
 *
 *       Filename:  const.h
 *
 *    Description:  Defines and constants.
 *
 *        Created:  03/27/2014 10:10:50 PM
 *
 *         Author:  David Keaton (davek), DavekDOS@gmail.com
 *
 * ==================================================================================
 */

#ifndef  CONST_INC
	#define  CONST_INC
/* version information */
#define DUDE_VERSION			0x0001
#define DUDE_VERSION_STRING		"0.01"
#define DUDE_VERSION_FMT		"[D]avid's [U]nreal [D]OOM [E]ditor v%s [compiled on %s @ %s]\n"
/* name of the default config file */
#define DUDE_CONFIG_FILE		"dude.ini"
/* we want our TRUE and FALSE ! */
#if !defined(TRUE) || !defined(FALSE)
	#define TRUE		1
	#define FALSE		0
#endif
/* enable if you want debug information by default */
#if defined(DEBUG)
	#define DEBUG_DEFAULT		TRUE
#else
	#define DEBUG_DEFAULT		FALSE
#endif
/* operating system constants */
#if defined(_WIN32) || defined(__WIN32) || defined(__WIN32__) || \
	defined(_WINNT) || defined(__WINNT__) || defined(__MINGW32__)
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
/* error codes */
#define E_UNKNOWN       -1                      /* unknown error, possible bug */
#define E_SUCCESS       0                       /* as the name implies! */
#define E_USAGE         1                       /* error code for when usage is printed, or version info is printed */
#define E_NOMEM         2                       /* unable to allocate the necessary memory */
#define E_BADPTR        3                       /* bad code pointer */
#define E_BADFILE       4                       /* unable to read/write file for whatever reason */
#define E_NOFILE        5                       /* unable to find the requested file, as it does not exist */
#define E_BADARG        6                       /* program argument error (didn't give an argument a value, etc) */
#define E_BOUNDS        7                       /* at some point we overstepped an array */
#define E_BADAPR        8                       /* APR error */
#define E_BADSDL        9                       /* SDL error */
#define E_BADLENGTH     10                      /* bad length or size of data (string, array, etc) */
#define E_KEYUSED       11                      /* the key requested has already been bound */
#define E_BADTYPE		12						/* bad enumerated/constant type given */
#define E_BADCONFIG     13                      /* error parsing the config file */
#define E_OSERROR       14                      /* operating system specific error */
/* these two are for inih */
#define E_INIH_ERROR	0
#define E_INIH_SUCCESS	1
/* size constants */
#define MAX_STRING      512                     /* maximum size for a string */
#define MAX_QUOTES      7                       /* great quotes from yours truly */
#define MAX_ARGS        128                     /* maximum amount of arguments the program can handle */
#define MAX_RESOURCES   512                     /* maximum amount of resources in resource_t */
#define MAX_DOOMSTRING  8                       /* typical size for a string identifier/name of an object in a WAD */
#define SUBSTRUCT_COUNT 3                       /* amount of substructs in settings_t */
/* constants for search function(s) */
#define SETTINGS_ALL            ((void *)-1)    /* search all possible settings substructs */
/* inih macros */
#define ini_match(s, n)			strcasecmp(section, s) == 0 && strcmp(name, n) == 0
#define ini_section(s)			strcasecmp(section, s) == 0
#define ini_name(n)				strcasecmp(name, n) == 0
/* string case-sensitive comparison macro */
#define match(x, y)				strcmp(x, y) == 0
/* string case-insensitive comparison macro */
#define match_i(x, y)			strcasecmp(x, y) == 0
/* error macros */
#define e_return(why,where)		rc = why; goto where
/* memory constants/macros */
#define MEM_CHUNK_SIZE  4096                    /* the size of apr_pool_palloc() chunks */
#define MEM_CHUNK_SHIFT 12                      /* the exact amount of bits to shift */
#define chunks_from_size(x)		(((x >> MEM_CHUNK_SHIFT) + 1) * MEM_CHUNK_SIZE)
/* key constants/macros */
#define KEY_NONE				SDLK_UNKNOWN
/* OPT_ARRAY constants */
#define ARRAY_END               ((void *)-1)    /* signifies the end of an OPT_ARRAY */
/* OS specific constants */
#if defined(OS_WINDOWS)
	#include <windef.h>
	#define PATH_DELIMITER	';'
	#define IWAD_DIR 		".;C:/doom2"
#elif defined(OS_CYGWIN)
	#include <limits.h>
	#define PATH_DELIMITER	':'
	#define IWAD_DIR 		".:/usr/local/share/games/doom"
#elif defined(OS_UNIX) && !defined(OS_CYGWIN)
	#include <linux/limits.h>
	#define PATH_DELIMITER	':'
	#define IWAD_DIR 		".:/usr/local/share/games/doom"
#elif defined(OS_MACOSX)                        //FIXME: What is the path delimiter on MACOSX? The default DOOM directory?
	#include <limits.h>
	#define PATH_DELIMITER	'?'
	#define IWAD_DIR 		".?/usr/local/share/games/doom"
#endif
#endif   /* ----- #ifndef CONST_INC  ----- */
/* vim: set sw=4 ts=4 ft=c: */

