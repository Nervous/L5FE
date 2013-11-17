#include "exec.h"

int exec_ruleuntil(s_list *rule_until)
{
    s_list *until = rule_until->node->son_list;
    int condition = 1;
    while(condition != 0)
        condition = exec_compound(until->brothers);
    return exec_dogroup(until->brothers->brothers);
}
