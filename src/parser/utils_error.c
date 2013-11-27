#include <stdlib.h>
#include <stdio.h>
#include "utils_error.h"
#include <termios.h>
#include <unistd.h>
#include <curses.h>
#include <term.h>

int parse_error(char *msg)
{
    extern s_global *g_global;
    g_global->parse_error = 2;
    if (g_global->file == 1)
    {
        printf("%s\nExiting ...\n", msg);
        exit(2);
        return 0;
    }
    else
    {
        return -1;
    }
}
