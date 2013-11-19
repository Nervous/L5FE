#include <string.h>
#include "exec.h"

/**
** @brief Execute the command rule
*/
int exec_command(s_list *ast)
{
    int ret = 0;
    if (!ast)
    {
        printf("PARSE ERROR\n");
        return -1;
    }
    if (strcmp(ast->node->str, "Simple_command") == 0)
        ret = exec_simplecommand(ast->son_list);
    else if (strcmp(ast->node->str, "Shell_command") == 0)
    {
        ret = exec_shellcommand(ast->son_list);
    }
    else if (strcmp(ast->node->str, "Funcdec") == 0)
    {
        ret = exec_funcdec(ast->son_list);
    }

    return ret;
}
