#include "builtins.h"
#include "../struct.h"
#include "../readline/history.h"
#include <curses.h>
#include <term.h>
#include <unistd.h>

extern s_global *g_global;

void exit_builtin(int n)
{
    write_history();
    tcsetattr(STDIN_FILENO, TCSANOW, &(g_global->attribute));
    if (n == -1)
        exit(1);
    else
        exit(n);
}
