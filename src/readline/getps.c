#include "../struct.h"
#include "../exec/variable.h"
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define _XOPEN_SOURCE

    extern s_global *g_global;

    static char *match_char3(int *i, char *val, char *buf)
    {
        if (val[*i] == 'w' || val[*i] == 'W')
            getcwd(buf, 256);
        else if (val[*i] == '$')
    {
        if (getuid() == 0)
            buf[0] = '#';
        else
            buf[0] = '$';
    }
    else if (val[*i] == '\\')
        buf[0] = '\\';
    else if (val[*i] == '[')
    {
        *i += 1;
        for (int j = *i; val[*i] != ']' && val[*i]; *i += 1)
            buf[*i - j] = val[*i];
    }
    return buf;
}

static char *match_char2(int *i, char *val, char *buf)
{
    int tmp = 0;

    if (val[*i] == 'h')
    {
        gethostname(buf, 256);
        tmp = 0;
        for (tmp = tmp; buf[tmp] != '.' && buf[tmp]; tmp++)
            ;
        buf[tmp] = '\0';
    }
    else if (val[*i] == 'H')
        gethostname(buf, 256);
    else if (val[*i] == 'n')
        buf[0] = '\n';
    else if (val[*i] == 'r')
        buf[0] = '\r';
    else if (val[*i] == 's')
        strcpy(buf, "42sh");
    else if (val[*i] == 'u')
    {
        char *buf_tmp = getlogin();
        strcpy(buf, buf_tmp);
    }
    else
        buf = match_char3(i, val, buf);
    return buf;
}

static char *match_char(int *i, char *val)
{
    *i += 1;
    char *buf = calloc(256, sizeof (char));
    time_t curtime = time(NULL);
    struct tm *loctime = localtime(&curtime);
    int tmp = 0;
    if (val[*i] == 'a')
        buf[0] = '\a';
    else if (val[*i] == 'd')
       strftime(buf, 256, "%a %b %d", loctime);
    else if (val[*i] == 'D')
    {
        tmp = *i + 2;
        for (*i = *i + 2; val[*i] && val[*i] != '}'; *i += 1)
            ;
        char *test = calloc(*i, sizeof (char));
        strcpy(test, val);
        test[*i] = '\0';
        strftime(buf, 256, &test[tmp], loctime);
        free(test);
    }
    else if (val[*i] == 'e')
        buf[0] = '\33';
    else
        buf = match_char2(i, val, buf);
    return buf;
}

static void aux_func(int i)
{
    g_global->ps_size = i;
    g_global->x_pos = i;
    g_global = g_global;
}

void getps(char *ps)
{
    char buf_tmp[2] = "";
    s_var *var = search_var(g_global->var, ps);
    if (!var)
    {
        write(STDIN_FILENO, "42sh$ ", 6);
        aux_func(6);
        return;
    }
    char *buf = var->value;
    char *n_ps = calloc(256, sizeof (char));
    for (int i = 0; buf[i]; i++)
        if (buf[i] == '\\')
        {
            char *tmp = match_char(&i, buf);
            strcat(n_ps, tmp);
            free(tmp);
        }
        else
        {
            buf_tmp[0] = buf[i];
            strcat(n_ps, buf_tmp);
        }
    aux_func(strlen(n_ps));
    write(1, n_ps, strlen(n_ps));
    free(n_ps);
}
