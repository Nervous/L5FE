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
    tputs(tgetstr("cr", NULL), 1, my_putchar);
    for (int i = 0; i < g_global->y_pos; i++)
        tputs(tgetstr("up", NULL), 1, my_putchar);
    for (int i = 0; i < g_global->ps_size; i++)
        tputs(tgetstr("nd", NULL), 1, my_putchar);
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
    tputs(tgetstr("cr", NULL), 1, my_putchar);
    for (int i = 0; i < ((len / tgetnum("co")) - g_global->y_pos); i++)
        tputs(tgetstr("do", NULL), 1, my_putchar);
    g_global->x_pos = len % tgetnum("co");
    g_global->y_pos = len / tgetnum("co");
    for (int i = 0; i < g_global->x_pos; i++)
        tputs(tgetstr("nd", NULL), 1, my_putchar);
    *cur_pos = *buf_s;
}

void ctrl_l(char **buf_p, int *cur_pos, int *buf_s, int *max_s)
{
    buf_p = buf_p;
    cur_pos = cur_pos;
    buf_s = buf_s;
    max_s = max_s;
    tputs(tgetstr("cl", NULL), 1, my_putchar);
    int tmp = g_global->x_pos;

    write_ps();
    write(STDOUT_FILENO, *buf_p, strlen(*buf_p));
    tputs(tgetstr("ho", NULL), 1, my_putchar);
    g_global->x_pos = tmp;
    for (int i = 0; i < g_global->y_pos; i++)
        tputs(tgetstr("do", NULL), 1, my_putchar);
    for (int i = 0; i < g_global->x_pos; i++)
        tputs(tgetstr("nd", NULL), 1, my_putchar);
}
