#include <string.h>
#include "exec.h"

int exec_shellcommand(s_list *ast)
{
    if (strcmp(ast->node->str, "Rule_if") == 0)
        return exec_if(ast->node->son_list);
    else if (strcmp(ast->node->str, "Rule_for") == 0)
        return exec_for(ast->node->son_list);
    else if (strcmp(ast->node->str, "Rule_while") == 0)
        return exec_while(ast->node->son_list);
    else if (strcmp(ast->node->str, "Rule_until") == 0)
        return exec_until(ast->node->son_list);
    else if (strcmp(ast->node->str, "Rule_case") == 0)
        return exec_case(ast->node->son_list);
    else if (strcmp(ast->node->str, "{")
             || strcmp(ast->node->str, "("))
    {
        ast = ast->brothers;
        return exec_compoundlist(ast->node->son_list);
        ast = ast->brothers;
    }
}
