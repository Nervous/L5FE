#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

char *get_dir(char *dir)
{
    DIR *dp;
    struct dirent *tmp;
    dp = opendir(dir);

    if (dp)
    {
        while ((tmp = readdir(dp)))
            printf("%s\n", tmp->d_name);

        closedir(dp);
    }
    return NULL;
}
