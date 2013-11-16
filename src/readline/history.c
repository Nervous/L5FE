#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../struct.h"

extern s_global *g_global;

void init_history(void)
{
    char *home = getenv("HOME");
    char *buf = malloc(sizeof (char) * (strlen(home) + 15));
    strcpy(buf, home);
    strcat(buf, "/.42sh_history");
    //g_global->hist = malloc(sizeof (FILE));
    g_global->hist = fopen(buf, "w+");
    g_global = g_global;
}

void write_history(char *line)
{
    fputs(line, g_global->hist);
    fputs("\n", g_global->hist);
}
