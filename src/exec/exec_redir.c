#include "exec.h"

int exec_redir(s_list *ast)
{
    switch (ast->node->str)
    {
    case ">":
        return exec_redir_output();
    case ">|":
        return exec_redir_output();
    case "<":
        return exec_redir_input();
    case ">>":
        return exec_redir_appendout();
    case "<<":
        return exec_redir_heredoc();
    case "<&":
        return exec_redir_dupin();
    case ">&":
        return exec_redir_dupout();
    case "<>":
        return exec_redir_rw();
    default:
        return -1;
    }
}
