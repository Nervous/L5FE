#include "readline.h"
#include "../struct.h"
#include "functionkey.h"
#include "history.h"
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <curses.h>
#include <term.h>
#include <string.h>
#define BUFFER_SIZE 10

extern s_global *g_global;

static void init_term(void)
{
    struct termios attribute;
    tcgetattr(STDIN_FILENO, &attribute);
    g_global->attribute = attribute;
    attribute.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &attribute);
    init_history();
}

static char term_buffer[BUFFER_SIZE];

int my_putchar(int ch)
{
    char c = ch;
    return (write(STDOUT_FILENO, &c, 1));
}

char get_char(void)
{
    char c;
    read(STDIN_FILENO, &c, 1);
    return c;
}

static void write_buf(char *buf, int cur_pos, int buf_size)
{
    buf_size = buf_size;
    write(STDOUT_FILENO, &buf[cur_pos], 1);
    tputs(tgetstr("sc", NULL), 1, my_putchar);
    write(STDOUT_FILENO, &buf[cur_pos + 1], strlen(&buf[cur_pos + 1]));
    write(STDOUT_FILENO, " ", 1);
    tputs(tgetstr("rc", NULL), 1, my_putchar);
}

static callback match_key(char c, char **buf)
{
    if (c == '\177')
        return backspace;
    if (c == '\n')
        return new_line;
    if (c == '\033')
    {
        char tmp = get_char();
        if (tmp == '[')
        {
            char tmp2 = get_char();
            if (tmp2 == 'D')
                return left_key;
            if (tmp2 == 'C')
                return right_key;
            if (tmp2 == '\n')
                return new_line;
        }
        if (tmp == '\n')
            return new_line;
        if (tmp < 32 || tmp == '\177')
            return match_key(tmp, buf);
    }
    return do_nothing;
}

static void process_input(char **buf_p, int *cur_pos, int *buf_s, int *max_s)
{
    char tmp;
    char *buf = *buf_p;
    while ((tmp = get_char()) != '\n')
    {
        if (tmp < 32 || tmp == '\177')
        {
            match_key(tmp, buf_p)(buf_p, cur_pos, buf_s, max_s);
            continue;
        }
        if (*buf_s >= *max_s)
        {
            *max_s += 100;
            *buf_p = realloc(*buf_p, sizeof (char) * *max_s);
            buf = *buf_p;
        }
        memcpy(*buf_p + *cur_pos + 1, *buf_p + *cur_pos, *buf_s - *cur_pos);
        buf[*cur_pos] = tmp;
        write_buf(buf, *cur_pos, *buf_s);
        *cur_pos += 1;
        *buf_s += 1;
    }
}

/**
 ** This funcution is responsible of setting up the variables for processing
 ** the input
 */
static char *read_input(void)
{
    write(STDIN_FILENO, "42sh$ ", 6);
    char *buf = calloc(100, sizeof (char));
    char *type = getenv("TERM");
    tgetent(term_buffer, type);
    int buf_size = 0;
    int cur_pos = 0;
    int max_size = 100;
    process_input(&buf, &cur_pos, &buf_size, &max_size);
    write(STDOUT_FILENO, "\n", 1);
    g_global->readline = buf;
    return buf;
}


void readline(void)
{
    init_term();
    char *buf;
    do {
        buf = read_input();
        write_history(buf);
        if (!strcmp(buf, "exit"))
        {
            free(buf);
            break;
        }
        free(buf);
    }
    while (1);
    fflush(g_global->hist);
    tcsetattr(STDIN_FILENO, TCSANOW, &(g_global->attribute));
}
