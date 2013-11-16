#include "exec.h"

int exec_simplecommand(s_list *simple_command)
{
    char **argv = build_argv(simple_command->node->son_list);
    return do_fork(char **argv);
    // CHAR **ARGV NOT FREE /!\
}
