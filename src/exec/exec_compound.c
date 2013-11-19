#include "exec.h"

/**
** @brief Execute the compound_list rule
*/
int exec_compound_aux(s_list *p_and_or)
{
    if (!p_and_or || p_and_or->son_list == NULL)
        return 0;
    else
        return exec_andor(p_and_or->son_list)
                          || exec_compound_aux(p_and_or->brothers);
}

int exec_compound(s_list *compound)
{
    return exec_compound_aux(compound);
}
