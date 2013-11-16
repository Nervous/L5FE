#include "exec.h"

int exec_if(s_list rule_if)
{
    s_list current = rule_if->node->son_list;
    /* current on if */
    int condition = exec_compound(current->brothers);
    current = current->brothers->brothers;
    /*current on then*/
    if (condition)
        return exec_compound(current->brothers);
    /* if current (which is now eq to fi or else) == else */
    else if ((current = current->brothers->brothers)->node->e_type == ELSE)
        return exec_compound(current->brothers);
    else
        return 0;
}
