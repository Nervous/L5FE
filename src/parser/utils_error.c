#include <stdlib.h>
#include <stdio.h>
#include "utils_error.h"

extern s_global *g_global;

int parse_error(char *msg)
{
    g_global->parse_error = -1;
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
