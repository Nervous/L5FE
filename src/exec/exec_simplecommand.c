#include "exec.h"
#include <string.h>

int exec_simplecommand(s_list *simple_command)
{
    while (simple_command)
    {
        if (simple_command->node->type == ASSIGNMENT_WORD)
        {
            return exec_var(simple_command->node->str);
        }
        else if (simple_command->node->type == WORD)
        {
            char **argv = build_argv(simple_command);
            return do_fork(argv);
        }
        else if (strcmp(simple_command->node->str, "Redirection") == 0)
            return exec_redir(simple_command->node->son_list);
        simple_command = simple_command->brothers;
    }
    return 1;
}
