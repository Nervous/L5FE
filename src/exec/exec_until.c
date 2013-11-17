#include "exec.h"

int exec_until(s_list *until)
{
    int condition = 1;
    int ret = 0;
    while (condition != 0)
    {
        condition = exec_compound(until->brothers->node->son_list);

        if (condition != 0)
            ret = exec_dogroup(until->brothers->brothers->node->son_list);
    }

    return ret;
}
