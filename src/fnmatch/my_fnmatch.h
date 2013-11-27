#ifndef MY_FNMATCH_H
# define MY_FNMATCH_H

#include "fifo.h"

int my_fnmatch(const char *pattern, const char *string);
void path_exp(char **str);
char *my_str_copy(char *str);
char **get_dir_list2(char *dir);

#endif /* !MY_FNMATCH */
