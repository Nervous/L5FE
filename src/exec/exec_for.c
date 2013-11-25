#include "exec.h"

extern s_global *g_global;
/**
** @brief Execute the for rule
*/
int exec_for(s_list *ast)
{
    int ret = 0;
    s_list *cpy = ast;

    while (strcmp(cpy->node->str, "Do_group") != 0)
        cpy = cpy->brothers;

    char *tmp = ast->brothers->node->str;

    if (ast->brothers->brothers && ast->brothers->brothers->node->type == IN)
    {
        ast = ast->brothers->brothers->brothers;
        while (ast->node->type == WORD)
        {
            if (g_global->break_nb > 0)
            {
                g_global->break_nb -= 1;
                return 0;
            }
            add_var(g_global->var, tmp, ast->node->str);
            ret = exec_dogroup(cpy->son_list);
            ast = ast->brothers;
        }
    }
    else
    {
        while (ast->node->type == WORD)
        {
            add_var(g_global->var, tmp, ast->node->str);
            ret = exec_dogroup(cpy->son_list);
            ast = ast->brothers;
        }
    }

    return ret;
}
