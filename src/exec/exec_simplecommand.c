#include "exec.h"
#include "function.h"
#include <string.h>

int exec_simplecommand(s_list *simple_command)
{
    s_function *tmp = NULL;
    if ((tmp = search_function(simple_command->node->str)) != NULL)
        exec_shellcommand(tmp->node->son_list);
    else
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
    }
    return 1;
}
