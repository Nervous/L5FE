#include "exec.h"
#include <string.h>

int exec_else(s_list *current)
{
    int condition = 1;
    while (current != NULL && current->node->type != ELSE)
    {
        condition = exec_compound(current->brothers);
        if (condition == 0) //current elif -> compound -> then -> compound
            return exec_compound(current->brothers->brothers->brothers);
        /* current elif -> compound -> then -> compound -> else of elif */
        current = current->brothers->brothers->brothers->brothers;
    }
    if (current == NULL)
        return 0;
    return exec_compound(current->brothers);
}

int exec_if(s_list *current)
{
    /* current on if */
    int condition = exec_compound(current->brothers);
    current = current->brothers->brothers;
    /*current on then*/
    if (condition == 0)
        return exec_compound(current->brothers);
    /* if current (which is now eq to fi or else) == "Else_clause" */
    else if (strcmp((current = current->brothers->brothers)->node->str,
                    "Else_clause"))
        return exec_else(current->brothers);
    else
        return 0;
}
