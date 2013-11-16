#include "exec.h"

int exec_else(s_list else_list)
{
    s_list current
    //if(
}

int exec_if(s_list rule_if)
{
    s_list current = rule_if->node->son_list;
    /* current on if */
    int condition = exec_compound(current->brothers);
    current = current->brothers->brothers;
    /*current on then*/
    if (condition)
        return exec_compound(current->brothers);
    /* if current (which is now eq to fi or else) == "Else_clause" */
    else if (strcmp((current = current->brothers->brothers)->node->str,
                    "Else_clause"))
        return exec_compound(current->brothers);
    else
        return 0;
}
