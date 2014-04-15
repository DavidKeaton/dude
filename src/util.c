/*
 * =====================================================================================
 *
 *       Filename:  util.c
 *
 *    Description:  Utility functions
 *
 *        Created:  03/29/2014  6:57:38 PM
 *
 *         Author:  David Keaton (davek), DavekDOS@gmail.com
 *
 * =====================================================================================
 */

#include "dude.h"
#include "util.h"
#include "options.h"
#include "log.h"


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  is_directory
 *  Description:  Tests whether a path is to a file or a directory. Returns TRUE if the
 *  	path given is a directory, FALSE if it is not.
 * =====================================================================================
 */
//int is_directory(const char *path)
//{
//	apr_status_t rv;
//	apr_finfo_t finfo;
//	apr_int32_t valid,wanted;
//	wanted = APR_FINFO_TYPE;
//	rv = apr_stat(&finfo, path, wanted, dude.mp.file);
//	valid = finfo.valid;
//	if((valid & wanted) != wanted) {
//		log_print(LOG_ERROR, "(apr) unable to get wanted attributes from finfo (rv: %d)", rv);
//		return E_BADAPR;
//	}
//	if(finfo.filetype == APR_DIR) {
//		return TRUE;
//	} else {
//		return FALSE;
//	}
//}		/* -----  end of function is_directory  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  walk_directory
 *  Description:  
 * =====================================================================================
 */
int walk_directory(const char *path)
{
	//TODO: IMPLEMENT
	return E_SUCCESS;
}		/* -----  end of function walk_directory  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  file_exists
 *  Description:  Determine whether a file exists or not. Returns TRUE if the file
 *  	exists, or FALSE if it does not.
 * =====================================================================================
 */
int file_exists(const char *filename)
{
	FILE *file;
	if((file = fopen(filename, "r")) == NULL) {
		return FALSE;
	}
	fclose(file);
	return TRUE;
}		/* -----  end of function file_exists  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  check_extension
 *  Description:  Determines whether the file ends with the given extension. Returns
 *  	TRUE if the file ends with the given extension, FALSE otherwise.
 * =====================================================================================
 */
int check_extension(const char *filename, const char *extension)
{
	char *p;
	unsigned int base_len, ext_len;
	if((p = strrchr(filename, '.')) == NULL) {
		/* unable to find the extension portion of the file */
		//TODO: Print error/log message.
		return FALSE;
	}
	base_len = strlen(filename);
	if((p - filename + 1) == base_len) {
		/* no extension following '.' */
		//TODO: Print error/log message.
		return FALSE;
	} else if((p - filename + 1) > base_len) {
		/* well, we have a weird error where we overstepped an array boundary */
		//TODO: Print error message.
		return E_BOUNDS;
	}
	/* go with the safer length */
	ext_len = strlen(extension);
#if defined(OS_WINDOWS)
	if(!match_i(extension, (p + 1))) {
#else
	if(!match(extension, (p + 1)))  {
#endif
		return FALSE;
	}
	return TRUE;
}		/* -----  end of function check_extension  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  check_magic
 *  Description:  Check the file header's "magic" signature, and determine if it is
 *  	valid. Returns TRUE if it is the same, FALSE otherwise.
 * =====================================================================================
 */
int check_magic(const char *filename, const char *magic, unsigned int len_magic, unsigned int offset)
{
	int rc = TRUE;
	FILE *file;
	char *data;
	/* read the file, and store the offset area of the same size into our buffer */
	if((file = fopen(filename, "rb")) == NULL) {
		//TODO: Print error/perror message here.
		return E_NOFILE;
	}
	if((data = malloc(len_magic)) == NULL) {
		//TODO: Print error message here.
		return E_NOMEM;
	}
	if(fseek(file, offset, SEEK_SET)) {
		/* error seeking to the offset, possibly went too far */
		//TODO: Print error message here.
		return E_BADFILE;
	}
	if(fread(data, len_magic, 1, file) != len_magic) {
		/* possibly read past end of file */
		//TODO: Print error message here.
		return E_BADFILE;
	}
	if(memcmp(data, magic, len_magic)) {
		/* the magics are not the same, return FALSE */
		rc = FALSE;
	}
data_end:
	free(data);
file_end:
	fclose(file);
	return rc;
}		/* -----  end of function check_magic  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  num_tokens
 *  Description:  Iterates through a string, and returns the number of tokens, specified
 *  	by the 'token' argument. Returns zero if no tokens are found.
 * =====================================================================================
 */
int num_tokens(const char *str, const char token)
{
	unsigned int amount;
	char *p = strchr(str, (int)token);
	for(amount = 0; p != NULL; ++amount) {
		p = strchr((p + 1), (int)token);
	}
	return amount;
}		/* -----  end of function num_tokens  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  tabs_to_spaces
 *  Description:  
 * =====================================================================================
 */
int tabs_to_spaces(char *array, unsigned int num_spaces)
{
	return E_SUCCESS;
}		/* -----  end of function tabs_to_spaces  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  align_text
 *  Description:  Aligns text based on 'alignment' and places the formatted 'text' into
 *  	'destination'. If the amount to write exceeds 'length', then E_BADLENGTH is
 *  	returned.
 *  	(Note: this aligns text using spaces, for an even look)
 * =====================================================================================
 */
int align_text(char *dest, unsigned int dest_len, const char *src, text_align_e alignment)
{
    char *offset;                               /* offset into 'dest' where 'src' will go */
    unsigned int src_len;                       /* length of the source string */
	src_len = strlen(src);
	if(src_len >= dest_len) {
		/* the text would overflow the destination */
		log_print(LOG_WARN, "buffer overflow: align_text dest=[0x%08X/%db] <- src=[0x%08X/%db]", dest, dest_len, src, src_len);
		return E_BADLENGTH;
	}
	/* set the buffer full of spaces to prepare for alignment */
	memset(dest, ' ', dest_len);
	/* depending on 'alignment' do the appropriate calculations */
	switch(alignment) {
		case TEXT_ALIGN_LEFT:
			offset = dest;
			break;
		case TEXT_ALIGN_CENTER:
			offset = (dest + ((dest_len - src_len) / 2));
			break;
		case TEXT_ALIGN_RIGHT:
			offset = (dest + (dest_len - src_len));
			break;
		default:
			log_print(LOG_ERROR, "unknown type for text alignment [type: 0x%X]", alignment);
			return E_BADTYPE;
	}
	if((offset >= (dest + dest_len)) || ((offset + src_len) >= (dest + dest_len))) {
		/* odd pointer error, let's not cross array bounds */
		log_print(LOG_ERROR, "bounds error: offset=[0x%08X] > dest=[0x%08X]", offset, dest);
		return E_BADPTR;
	}
	memcpy(offset, src, src_len);
	dest[dest_len - 1] = '\0';
	log_print(LOG_DEBUG, "align_text [spaces: %d/total: %d]\n\t-> ['%s']", (dest_len - src_len), dest_len, dest);
	return E_SUCCESS;
}		/* -----  end of function align_text  ----- */












/* vim: set sw=4 ts=4 ft=c: */

