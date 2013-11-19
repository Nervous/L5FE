#include <string.h>
#include "exec.h"

int exec_shellcommand(s_list *ast)
{
    if (strcmp(ast->node->str, "Rule_if") == 0)
        return exec_if(ast->son_list);
    else if (strcmp(ast->node->str, "Rule_for") == 0)
        return exec_for(ast->son_list);
    else if (strcmp(ast->node->str, "Rule_while") == 0)
        return exec_while(ast->son_list);
    else if (strcmp(ast->node->str, "Rule_until") == 0)
        return exec_until(ast->son_list);
    else if (strcmp(ast->node->str, "Rule_case") == 0)
        return exec_case(ast->son_list);
    else if (strcmp(ast->node->str, "{")
             || strcmp(ast->node->str, "("))
    {
        ast = ast->brothers;
        int ret = exec_compound(ast->son_list);
        ast = ast->brothers;
        return ret;
    }
    return 0;
}
