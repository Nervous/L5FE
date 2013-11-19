#include "readline.h"
#include "../struct.h"
#include "../parser/parser.h"
#include "../exec/exec.h"
#include "../ast/ast.h"
#include "functionkey.h"
#include "history.h"
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <curses.h>
#include <term.h>
#include <string.h>

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


int my_putchar(int ch)
{
    char c = ch;
    return write(STDOUT_FILENO, &c, 1);
}

static char get_char(void)
{
    char c;
    read(STDIN_FILENO, &c, 1);
    return c;
}

void write_buf(char *buf, int cur_pos, int buf_size)
{
    buf_size = buf_size;
    write(STDOUT_FILENO, &buf[cur_pos], 1);
    tputs(tgetstr("sc", NULL), 1, my_putchar);
    write(STDOUT_FILENO, &buf[cur_pos + 1], strlen(&buf[cur_pos + 1]));
    write(STDOUT_FILENO, " ", 1);
    tputs(tgetstr("rc", NULL), 1, my_putchar);
}

static callback match_esc_key(char tmp)
{
    if (tmp == '[')
    {
        char tmp2 = get_char();
        if (tmp2 == 'D')
            return left_key;
        if (tmp2 == 'C')
            return right_key;
        if (tmp2 == 'A')
            return up_key;
        if (tmp2 == 'B')
            return down_key;
        if (tmp2 == '3' && get_char() == '~')
            return delete;
    }
    if (tmp == '\n')
        return new_line;
    return do_nothing;
}

/**
 ** @brief This function match key with special keys
 */
static callback match_key(char c, char **buf)
{
    if (c == '\177' || c == '\b')
        return backspace;
    if (c == '\n'|| c == '\r')
        return new_line;
    if (c == '\033')
    {
        char tmp = get_char();
        return match_esc_key(tmp);
        if (tmp < 32 || tmp == '\177')
            return match_key(tmp, buf);
    }
    return do_nothing;
}

static void process_input(char **buf_p, int *cur_pos, int *buf_s, int *max_s)
{
    char tmp;
    char *buf = *buf_p;
    while ((tmp = get_char()) != '\n' && tmp != '\r')
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
        memmove(*buf_p + *cur_pos + 1, *buf_p + *cur_pos, *buf_s - *cur_pos);
        buf[*cur_pos] = tmp;
        write_buf(buf, *cur_pos, *buf_s);
        *cur_pos += 1;
        *buf_s += 1;
    }
}

/**
 ** @brief This function is responsible of setting up the variables for
 ** processing the input in PS1
 */
static void read_input(void)
{
    if (g_global->readline != NULL)
    {
        free(g_global->readline);
        g_global->readline = NULL;
    }
    write(STDIN_FILENO, "42sh$ ", 6);
    char *buf = NULL;
    buf = calloc(100, sizeof (char));
    int buf_size = 0;
    int cur_pos = 0;
    int max_size = 100;
    process_input(&buf, &cur_pos, &buf_size, &max_size);
    write(STDOUT_FILENO, "\n", 1);
    g_global->readline = buf;
}

/**
 ** @brief This function is responsible of setting up the variables for
 ** processing the input in PS2
 */
static void read_ps2(void)
{
    write(STDIN_FILENO, "> ", 2);
    char *buf = calloc(100, sizeof (char));
    int buf_size = 0;
    int cur_pos = 0;
    int max_size = 100;
    process_input(&buf, &cur_pos, &buf_size, &max_size);
    write(STDOUT_FILENO, "\n", 1);
    g_global->readline = realloc(g_global->readline,
            sizeof (char) * (strlen(g_global->readline) + buf_size + 1));
    strcat(g_global->readline, buf);
    free(buf);
}

void write_ps(void)
{
    if (g_global->readline == NULL)
        write(STDIN_FILENO, "42sh$ ", 6);
    else
        write(STDIN_FILENO, "> ", 2);
}

/**
 ** @brief This function is responsible of setting up the terminal and
 ** the termcap data
 */
void readline(void)
{
    init_term();
    char *type = getenv("TERM");
    char term_buffer[2048];
    tgetent(term_buffer, type);
    do {
        read_input();
        if (!strcmp(g_global->readline, "exit"))
            break;
        while (parse() == -1)
        {
            g_global->pos = 0;
            release_ast(get_root(g_global->current_node));
            read_ps2();
        }
        g_global->pos = 0;
        exec_input(get_root(g_global->current_node));
        release_ast(get_root(g_global->current_node));
        g_global->current_node = NULL;
        add_to_hist(g_global->readline);
        g_global->hist_ind = -1;
    }
    while (1);
    write_history();
    tcsetattr(STDIN_FILENO, TCSANOW, &(g_global->attribute));
}
