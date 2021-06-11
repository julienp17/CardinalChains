#ifndef FILE_READING_H_
#define FILE_READING_H_

#include <stdbool.h>

unsigned int get_file_size(char const *filepath);
char *get_file_buffer(char const *filepath);
char **get_file_lines(char const *pathname);
char **my_str_to_word_array(char *str, char const sep);
unsigned int my_strarr_len(char * const *arr);
unsigned int my_count_char(char const *str, char const to_count);
unsigned int my_count_until_sep(char const *str, char const sep);
bool my_str_isnum_pos(char const *str);

#endif