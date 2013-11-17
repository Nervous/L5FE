#include <stdlib.h>
#include <stdio.h>
#include "utils_error.h"

extern s_global *g_global;

int parse_error(char *msg)
{
    if (g_global->file == 1)
    {
        printf("%s\nExiting ...\n", msg);
        exit(1);
        return 0;
    }
    else
    {
        return -1;
    }
}
