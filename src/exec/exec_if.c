#include "exec.h"
#include <string.h>

int exec_else(s_list *current)
{
    int condition = 1;
    /* current = elif or else */
    while (current != NULL && current->node->type != ELSE)
    {
        condition = exec_compound(current->brothers->node->son_list);
        if (condition == 0) //current elif -> compound -> then -> compound
            return
exec_compound(current->brothers->brothers->brothers->node->son_list);
        /* current elif -> compound -> then -> compound -> else of elif */
        if (current->brothers->brothers->brothers->brothers)
            current =
            current->brothers->brothers->brothers->brothers->node->son_list;
        else
            return 0;
    }
    if (current == NULL)
        return 0;
    return exec_compound(current->brothers->node->son_list);
}

int exec_if(s_list *current)
{
    /* current on if */
    int condition = exec_compound(current->brothers->node->son_list);
    current = current->brothers->brothers;
    /*current on then*/
    if (condition == 0)
        return exec_compound(current->brothers->node->son_list);
    /* if current (which is now eq to fi or else) == "Else_clause" */
    else if (strcmp((current = current->brothers->brothers)->node->str,
                    "Else_clause") == 0)
        return exec_else(current->node->son_list);
    else
        return 0;
}
