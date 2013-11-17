#include "exec.h"

int exec_until(s_list *until)
{
    int condition = 1;
    while (condition != 0)
        condition = exec_compound(until->brothers);
    return exec_dogroup(until->brothers->brothers);
}
