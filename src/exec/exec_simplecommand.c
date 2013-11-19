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
        simple_command = simple_command->brothers;
    }
    return 1;
}
