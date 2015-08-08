#ifndef  UTIL_INC
#define  UTIL_INC

#include <string>

/** text_align_type
 * Tells `align_text()' how to align the text given.
 */
enum text_align_type {
    ALIGN_LEFT,
    ALIGN_CENTER,
    ALIGN_RIGHT
};

namespace dude {
/* boolean routines */
int get_boolean(const char *value);
int is_true(const char *value);
int is_false(const char *value);

// TODO: create list class?
    /* list routines */
    unsigned int get_list_length(void **list);
    int append_list_item(void **list, void *item);
// TODO: Export to io class?
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
// aligns a string, with a given length (default to 80)
std::string align_text(const std::string &str, text_align_type align, int len=80);
}
#endif   /* ----- #ifndef UTIL_INC  ----- */
/* vim: set sw=4 ts=4 sts=4 ft=cpp expandtab: */
