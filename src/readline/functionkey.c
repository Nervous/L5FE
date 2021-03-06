#include "readline.h"
#include "../struct.h"
#include "history.h"
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <term.h>
#include <string.h>
#include "functionkey.h"

extern s_global *g_global;

void backspace(char **buf_p, int *cur_pos, int *buf_s, int *max_s)
{
    max_s = max_s;
    char *buf = *buf_p;
    if (*cur_pos > 0)
    {
        memmove(buf + *cur_pos - 1, buf + *cur_pos, *buf_s - *cur_pos + 1);
        left_key(buf_p, cur_pos, buf_s, max_s);
        *buf_s -= 1;
        tputs(tgetstr("sc", NULL), 1, my_putchar);
        write(STDOUT_FILENO, buf + *cur_pos, strlen(buf + *cur_pos));
        write(STDOUT_FILENO, " ", 1);
        tputs(tgetstr("rc", NULL), 1, my_putchar);
    }
}

void delete(char **buf_p, int *cur_pos, int *buf_size, int *max_size)
{
    max_size = max_size;
    char *buf = *buf_p;
    if (*cur_pos < *buf_size)
    {
        memmove(buf + *cur_pos, buf + *cur_pos + 1, *buf_size - *cur_pos + 1);
        *buf_size -= 1;
        tputs(tgetstr("sc", NULL), 1, my_putchar);
        write(STDOUT_FILENO, buf + *cur_pos, strlen(buf + *cur_pos));
        write(STDOUT_FILENO, " ", 1);
        tputs(tgetstr("rc", NULL), 1, my_putchar);
    }
}

void delete_end(char **buf_p, int *cur_pos, int *buf_size, int *max_size)
{
    buf_p = buf_p;
    cur_pos = cur_pos;
    buf_size = buf_size;
    max_size = max_size;
    tputs(tgetstr("ce", NULL), 1, my_putchar);
    char *tmp = *buf_p;
    for (int i = *cur_pos; tmp[i]; i++)
        tmp[i] = '\0';
    *buf_size = *cur_pos;
}

void new_line(char **buf, int *cur_pos, int *buf_size, int *max_size)
{
    buf = buf;
    cur_pos = cur_pos;
    buf_size = buf_size;
    max_size = max_size;
}

void do_nothing(char **buf, int *cur_pos, int *buf_size, int *max_size)
{
    buf = buf;
    cur_pos = cur_pos;
    buf_size = buf_size;
    max_size = max_size;
}
