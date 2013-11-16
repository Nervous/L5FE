#include "exec.h"

int exec_else(s_list else_list)
{
    int condition = 0;
    s_list current = else_list->node->son_list;
    while (current != NULL && current->node->type != ELSE)
    {
        condition = exec_compound(current->brothers):
        if (condition) //current elif -> compound -> then -> compound
            return exec_compound(current->brothers->brothers->brothers);
        /* current elif -> compound -> then -> compound -> else of elif */
        current = current->brothers->brothers->brothers->brothers;
    }
    if (current == NULL)
        return 0;
    return exec_compound(current->brothers);
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
        return exec_else(current->brothers);
    else
        return 0;
}
