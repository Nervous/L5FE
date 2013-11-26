#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include "my_fnmatch.h"

static char *my_str_copy(char *str)
{
    char *result = malloc((strlen(str) + 1) * sizeof(char));
    result = strcpy(result, str);
    return result;
}

char **get_dir_list(char *dir)
{
    DIR *dp;
    struct dirent *tmp;
    int dir_count = 0;
    char **dir_list = malloc(sizeof(char*));
    dir_list[0] = NULL;
    dp = opendir(dir);
    if (dp)
    {
        while ((tmp = readdir(dp)))
        {
            dir_list[dir_count] = my_str_copy(tmp->d_name);
            dir_count++;
            dir_list = realloc(dir_list, dir_count + 2);
        }

        closedir(dp);
    }
    return NULL;
}
