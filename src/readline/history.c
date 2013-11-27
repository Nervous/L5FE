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
    g_global->hist_arr = calloc(200, sizeof (char *));
    g_global->hist_ind = -1;
    if (file)
    {
        size_t len = 0;
        for (int i = 0; i < 200; i++)
        {
            getline(&g_global->hist_arr[i], &len, file);
            g_global->hist_arr[i][strlen(g_global->hist_arr[i]) - 1] = '\0';
        }
        fclose(file);
    }
    else
    {
        for (int i = 0; i < 200; i++)
            g_global->hist_arr[i] = calloc(10, sizeof (char));

    }
}

void free_history(void)
{
    for (int i = 0; i < 200; i++)
    {
        free(g_global->hist_arr[i]);
    }
    free(g_global->hist_arr);
}

void write_history(void)
{
    FILE *file = fopen(g_global->hist_file, "w");
    for (int i = 0; i < 200; i++)
    {
        fputs(g_global->hist_arr[i], file);
        fputc('\n', file);
    }
}

void add_to_hist(char *buf)
{
    if (strcmp(buf, g_global->hist_arr[0]) == 0)
        return;
    char *tmp = calloc(strlen(buf) + 1, sizeof (char));
    strcpy(tmp, buf);
    free(g_global->hist_arr[199]);
    memmove(g_global->hist_arr + 1, g_global->hist_arr, sizeof (char *) * 199);
    g_global->hist_arr[0] = tmp;
}

char *get_history_ln(void)
{
    if (g_global->hist_ind == -1)
        return "";
    return g_global->hist_arr[g_global->hist_ind];
}
