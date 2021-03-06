#include "builtins.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

extern s_global *g_global;
static int display_hist(void)
{
    char *number = NULL;
    for (int i = 0; g_global->hist_arr[i]; i++)
    {
        if (strlen(g_global->hist_arr[i]) > 0)
        {
            if (i == 0)
                my_puts("0");
            else
            {
                number = my_itoa(i);
                my_puts(number);
                free(number);
            }
            my_puts("  ");
            my_puts(g_global->hist_arr[i]);
            my_puts("\n");
        }
    }
    return 0;
}

int my_history(s_list *ast)
{
    if (!ast)
        display_hist();
    return 0;
}
