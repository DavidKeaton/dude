/*
 * =====================================================================================
 *
 *       Filename:  util.h
 *
 *    Description:  Utility functions
 *
 *        Created:  03/29/2014  6:57:51 PM
 *
 *         Author:  David Keaton (davek), DavekDOS@gmail.com
 *
 * =====================================================================================
 */


#ifndef  UTIL_INC
	#define  UTIL_INC
#include "dude.h"

/* file/directory routines */
int is_directory(const char *path);
int walk_directory(const char *path);
int file_exists(const char *filename);
/* validation routines */
int check_extension(const char *filename, const char *extension);
int check_magic(const char *filename, const char *magic, unsigned int len_magic, unsigned int offset);
/* string routines */
int num_tokens(const char *str, const char token);
int tabs_to_spaces(char *array, unsigned int num_spaces);
int align_text(char *dest, unsigned int desT_len, const char *src, text_align_e alignment);
#endif   /* ----- #ifndef UTIL_INC  ----- */
/* vim: set sw=4 ts=4 ft=c: */

