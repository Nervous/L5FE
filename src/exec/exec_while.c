#include "exec.h"

int exec_while(s_list *while_node)
{
    int condition = 0;
    while (condition == 0)
        condition = exec_compound(while_node->brothers);
    return exec_dogroup(while_node->brothers->brothers);
}
