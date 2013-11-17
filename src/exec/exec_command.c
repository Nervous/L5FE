#include <string.h>
#include "exec.h"

void exec_command(s_list *ast)
{
    if (strcmp(ast->node->son_list->node->str, "Simple_command") == 0)
        exec_simplecommand(ast->node->son_list);
    else if (strcmp(ast->node->son_list->node->str, "Shell_command") == 0)
        exec_shellcommand(ast->node->son_list);
    else if (strcmp(ast->node->son_list->node->str, "Funcdec") == 0)
        exec_funcdec(ast->node->son_list);
}
