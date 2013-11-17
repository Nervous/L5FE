#include "exec.h"

int exec_simplecommand(s_list *simple_command)
{
    char **argv = build_argv(simple_command);
    return do_fork(argv);
}
