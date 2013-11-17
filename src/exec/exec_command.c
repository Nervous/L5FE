#include "exec.h"

int exec_command(s_list *ast)
{
    int ert = 0;

    if (strcmp(ast->node->str, "Simple_command") == 0)
        ret = exec_simplecommand(ast->node->son_list);
    else if (strcmp(ast->node->str, "Shell_command") == 0)
    {
        ret = exec_shellcommand(ast->node->son_list);

        while (ast->brothers)
        {
            ret = exec_redirection(ast->brothers);
            ast = ast->brothers;
        }
    }
    else if (strcmp(ast->node->str, "Funcdec") == 0)
    {
        ret = exec_funcdec(ast->node->son_list);

        while (ast->brothers)
        {
            ret = exec_redirection(ast->brothers);
            ast = ast->brothers;
        }
    }

    return ret;
}
