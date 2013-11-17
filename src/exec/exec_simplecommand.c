#include "exec.h"

int exec_simplecommand(s_list *simple_command)
{
    while (simple_command)
    {
        if (simple_command->type == ASSIGNMENT_WORD)
        {
//            return exec_var(simple_command->node->str);
        }
        else if (simple_command->type == WORD)
        {
            char **argv = build_argv(simple_command);
            return do_fork(char **argv);
        }
        else if (simple_command->node->str == "Redirection")
            return exec_redir(simple_command->son_list);
        simple_command = simple_command->brothers;
    }
}
