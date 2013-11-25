#include <string.h>
#include "function.h"
#include "exec.h"

int exec_simplecommand(s_list *simple_command)
{
    s_function *tmp = NULL;
    int ret = 0;
    char *str = NULL;
    if ((tmp = search_function(simple_command->node->str)) != NULL)
        ret = exec_shellcommand(tmp->node->son_list);
    else if ((ret = check_builtin(simple_command)) != -1)
        return ret;
    else if ((str = alias_get_value(simple_command->node->str)) != NULL)
        return exec_alias(simple_command, str);
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
    return ret;
}
