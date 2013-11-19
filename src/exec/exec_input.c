#include "exec.h"
#include <string.h>

int exec_input(s_list *ast)
{
    if (!ast || !(ast->son_list))
        return -1;
    else
        ast = ast->son_list;
    int ret = 0;
    while (ast)
    {
        if (strcmp(ast->node->str, "List") == 0)
            ret = exec_list(ast->son_list);
        else
            return 0;
        ast = ast->brothers;
    }
    return ret;
}
