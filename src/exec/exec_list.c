#include "exec.h"

void exec_list(s_list *ast)
{
    exec_andor(ast->node->son_list);

    while (ast->node->son_list->brothers)
    {
        if (ast->node->son_list->brothers->node->type == BIT_AND
            || ast->node->son_list->brothers->node->type == SEMICOLON)
            if (ast->node->son_list->brothers->brothers)
                exec_andor(ast->node->son_list->brothers->brothers);

        ast = ast->node->son_list->brothers;
    }
}
