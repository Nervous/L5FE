#include "builtins.h"
#include "../struct.h"
#include "../readline/history.h"
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <curses.h>
#include <term.h>

extern s_global *g_global;

void exit_builtin(int n)
{
    if (!g_global->file)
    {
        write_history();
        tcsetattr(STDIN_FILENO, TCSANOW, &(g_global->attribute));
    }
    if (n == -1)
    {
        exit(1);
    }
    else
        exit(n);
}
