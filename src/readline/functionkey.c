#include "readline.h"
#include "../struct.h"
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <curses.h>
#include <term.h>
#include <string.h>

int my_putchar(int ch);

void right_key (char **buf, int *cur_pos, int *buf_size, int *max_size)
{
    buf = buf;
    max_size = max_size;
    if (*cur_pos < *buf_size)
    {
        char *tmp = tgetstr("nd", NULL);
        tputs(tmp, 1, my_putchar);
        *cur_pos += 1;
    }
}

void left_key (char **buf, int *cur_pos, int *buf_size, int *max_size)
{
    buf = buf;
    buf_size = buf_size;
    max_size = max_size;
    if (*cur_pos > 0)
    {
        char *tmp = tgetstr("le", NULL);
        tputs(tmp, 1, my_putchar);
        *cur_pos -= 1;
    }
}


void backspace (char **buf_p, int *cur_pos, int *buf_s, int *max_s)
{
    max_s = max_s;
    char *buf = *buf_p;
    if (*cur_pos > 0)
    {
        memcpy(buf + *cur_pos - 1, buf + *cur_pos, *buf_s - *cur_pos + 1);
        char *tmp = tgetstr("le", NULL);
        tputs(tmp, 1, my_putchar);
        *cur_pos -= 1;
        *buf_s -= 1;
        tputs(tgetstr("sc", NULL), 1, my_putchar);
        write(STDOUT_FILENO, buf + *cur_pos, strlen(buf + *cur_pos));
        write(STDOUT_FILENO, " ", 1);
        tputs(tgetstr("rc", NULL), 1, my_putchar);
    }
}

void delete (char **buf_p, int *cur_pos, int *buf_size, int *max_size)
{
    max_size = max_size;
    char *buf = *buf_p;
    if (*cur_pos < *buf_size)
    {
        memcpy(buf + *cur_pos, buf + *cur_pos + 1, *buf_size - *cur_pos + 1);
        *buf_size -= 1;
        tputs(tgetstr("sc", NULL), 1, my_putchar);
        write(STDOUT_FILENO, buf + *cur_pos, strlen(buf + *cur_pos));
        write(STDOUT_FILENO, " ", 1);
        tputs(tgetstr("rc", NULL), 1, my_putchar);
    }
}

void new_line (char **buf, int *cur_pos, int *buf_size, int *max_size)
{
    buf = buf;
    cur_pos = cur_pos;
    buf_size = buf_size;
    max_size = max_size;
}

void do_nothing (char **buf, int *cur_pos, int *buf_size, int *max_size)
{
    buf = buf;
    cur_pos = cur_pos;
    buf_size = buf_size;
    max_size = max_size;
}
