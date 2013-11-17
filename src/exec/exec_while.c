#include "exec.h"

int exec_while(s_list *while_node)
{
    int condition = 0;
    int ret = 0;
    while (condition == 0)
    {
        condition = exec_compound(while_node->brothers->node->son_list);
        if (condition == 0)
            ret = exec_dogroup(while_node->brothers->brothers->node->son_list);
    }

    return ret;
}
