#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include "my_fnmatch.h"

char *my_str_copy(char *str)
{
    char *result = malloc((strlen(str) + 1) * sizeof(char));
    result = strcpy(result, str);
    return result;
}

char **get_dir_list2(char *dir)
{
    DIR *dp;
    struct dirent *tmp;
    int dir_count = 0;
    char **dir_list2 = malloc(sizeof(char*));
    dir_list2[0] = NULL;
    dp = opendir(dir);
    if (dp)
    {
        while ((tmp = readdir(dp)))
        {
            dir_list2[dir_count] = strdup(tmp->d_name);
            dir_count++;
            dir_list2 = realloc(dir_list2, dir_count + 1);
            dir_list2[dir_count] = NULL;
        }
        closedir(dp);
    }
    return dir_list2;
}
