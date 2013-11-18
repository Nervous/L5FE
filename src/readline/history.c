#define _GNU_SOURCE
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
    g_global->hist_file = buf;
    FILE *file = fopen(buf, "r");
    g_global->hist_arr = calloc(200, sizeof(char *));
    g_global->hist_ind = 0;
    size_t len = 0;
    for (int i = 0; i < 200; i++)
        getline(&g_global->hist_arr[i], &len, file);
    fclose(file);
}

void write_history(char *line)
{
    line = line;
    /*
    fputs(line, g_global->hist);
    fputs("\n", g_global->hist);
    */
}

char *get_history_ln(void)
{
    return g_global->hist_arr[g_global->hist_ind];
}
