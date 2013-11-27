#include "readline.h"
#include "../struct.h"
#include "history.h"
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <term.h>
#include <string.h>

extern s_global *g_global;

void ctrl_a(char **buf_p, int *cur_pos, int *buf_s, int *max_s)
{
    buf_p = buf_p;
    max_s = max_s;
    buf_s = buf_s;
    for (int i = 0; i < g_global->y_pos; i++)
        tputs(tgetstr("up", NULL), 1, my_putchar);
    for (int i = 0; i < g_global->ps_size - g_global->x_pos; i++)
        tputs(tgetstr("nd", NULL), 1, my_putchar);
    for (int i = 0; i < g_global->x_pos - g_global->ps_size; i++)
        tputs(tgetstr("le", NULL), 1, my_putchar);
    g_global->x_pos = g_global->ps_size;
    g_global->y_pos = 0;
    *cur_pos = 0;
}

void ctrl_e(char **buf_p, int *cur_pos, int *buf_s, int *max_s)
{
    buf_p = buf_p;
    max_s = max_s;
    buf_s = buf_s;
    int len = *buf_s + g_global->ps_size;
    for (int i = 0; i < len / tgetnum("co"); i++)
        tputs(tgetstr("do", NULL), 1, my_putchar);
    for (int i = 0; i < len % tgetnum("co") - g_global->x_pos; i++)
        tputs(tgetstr("nd", NULL), 1, my_putchar);
    for (int i = 0; i < g_global->x_pos - len % tgetnum("co"); i++)
        tputs(tgetstr("le", NULL), 1, my_putchar);
    g_global->x_pos = len % tgetnum("co");
    g_global->y_pos =  len / tgetnum("co");
    *cur_pos = *buf_s;
}

