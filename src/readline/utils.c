#include "../struct.h"
#include "readline.h"
#include <curses.h>
#include <term.h>

extern s_global *g_global;

void add_char(void)
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
        g_global->x_pos += 1;
    }
}
