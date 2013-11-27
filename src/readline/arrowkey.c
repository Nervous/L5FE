#include "readline.h"
#include "../struct.h"
#include "history.h"
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <curses.h>
#include <term.h>
#include <string.h>

extern s_global *g_global;

void right_key(char **buf, int *cur_pos, int *buf_size, int *max_size)
{
    buf = buf;
    max_size = max_size;
    if (*cur_pos < *buf_size)
    {
        if (g_global->x_pos >= tgetnum("co"))
        {
            g_global->x_pos = 0;
            g_global->y_pos += 1;
            for (int i = 0; i < tgetnum("co"); i++)
                tputs(tgetstr("le", NULL), 1, my_putchar);
            tputs(tgetstr("do", NULL), 1, my_putchar);
        }
        else
        {
            tputs(tgetstr("nd", NULL), 1, my_putchar);
            g_global->x_pos += 1;
        }
        *cur_pos += 1;
    }
}

void left_key(char **buf, int *cur_pos, int *buf_size, int *max_size)
{
    buf = buf;
    buf_size = buf_size;
    max_size = max_size;
    if (*cur_pos > 0)
    {
        if (g_global->x_pos == 0 && g_global->y_pos > 0)
        {
            g_global->x_pos = tgetnum("co");
            g_global->y_pos -= 1;
            for (int i = 0; i < tgetnum("co"); i++)
                tputs(tgetstr("nd", NULL), 1, my_putchar);
            tputs(tgetstr("up", NULL), 1, my_putchar);
        }
        else
        {
            g_global->x_pos -= 1;
            char *tmp = tgetstr("le", NULL);
            tputs(tmp, 1, my_putchar);
        }
        *cur_pos -= 1;
    }
}

void up_key(char **buf, int *cur_pos, int *buf_size, int *max_size)
{
    if (g_global->hist_ind < 200)
        g_global->hist_ind += 1;
    free(*buf);
    char *tmp = get_history_ln();
    int len = strlen(tmp);
    *max_size = len + 100;
    *buf_size = len;
    tputs(tgetstr("cr", NULL), 1, my_putchar);
    tputs(tgetstr("ce", NULL), 1, my_putchar);
    write_ps();
    g_global->x_pos = len + g_global->ps_size;
    write(STDIN_FILENO, tmp, len);
    *cur_pos = *buf_size;
    *buf = calloc(len + 100, sizeof (char));
    *buf = strcpy(*buf, tmp);
}

void down_key(char **buf, int *cur_pos, int *buf_size, int *max_size)
{
    if (g_global->hist_ind >= 0)
        g_global->hist_ind -= 1;
    else
        return;
    free(*buf);
    char *tmp = get_history_ln();
    int len = strlen(tmp);
    *max_size = len;
    *buf_size = len;
    tputs(tgetstr("cr", NULL), 1, my_putchar);
    tputs(tgetstr("ce", NULL), 1, my_putchar);
    g_global->x_pos = len;
    write_ps();
    write(STDIN_FILENO, tmp, len);
    *cur_pos = *buf_size;
    *buf = calloc(len + 1, sizeof (char));
    *buf = strcpy(*buf, tmp);
}
