#include "exec.h"

extern s_global *g_global;
int exec_while(s_list *while_node)
{
    int condition = 0;
    int ret = 0;
    while (condition == 0)
    {
        condition = exec_compound(while_node->brothers->son_list);
        if (condition == 0)
            ret = exec_dogroup(while_node->brothers->brothers->son_list);
        if (g_global->break_nb > 0)
        {
            g_global->break_nb -= 1;
            return 0;
        }
    }

    return ret;
}
