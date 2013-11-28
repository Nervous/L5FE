#ifndef MY_FNMATCH_H
# define MY_FNMATCH_H

char **get_dir_list2(char *dir);
int my_fnmatch(const char *pattern, const char *string);
void path_exp(char **str);

#endif /* !MY_FNMATCH_H */
