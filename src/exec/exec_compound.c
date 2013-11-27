#include "exec.h"
#include <string.h>

/**
** @brief Execute the compound_list rule
*/
extern s_global *g_global;
int exec_compound_aux(s_list *p_and_or)
{
    if (g_global->break_nb <= 0)
    {
        if (p_and_or && strcmp(p_and_or->node->str, ";") == 0)
            p_and_or = p_and_or->brothers;
        if (!p_and_or || p_and_or->son_list == NULL)
            return 0;
        else
            return exec_andor(p_and_or->son_list)
                              || exec_compound_aux(p_and_or->brothers);
    }
    else
        return 0;
}

int exec_compound(s_list *compound)
{
    return exec_compound_aux(compound);
}
