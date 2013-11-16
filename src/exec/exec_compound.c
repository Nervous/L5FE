#include "exec.h"

int exec_compound_aux(s_list *p_and_or)
{
    if (p_and_or == NULL)
        return 1;
    else
        return exec_and_or(p_and_or) && exec_compound_aux(p_and_or->brothers);
}

int exec_compound(s_list *compound)
{
    return exec_compound_aux(compound->node->son_list);
}
