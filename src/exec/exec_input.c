#include "exec.h"
#include <string.h>

int exec_input(s_list *ast)
{
    if (!ast || !(ast->node->son_list))
        return -1;
    else
        ast = ast->node->son_list;
    int ret = 0;
    while (ast)
    {
        if (strcmp(ast->node->str, "List") == 0)
            ret = exec_list(ast->node->son_list);
        else
            return 0;
        ast = ast->brothers;
    }
    return ret;
}
