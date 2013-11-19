#include "exec.h"

int exec_redir(s_list *ast)
{
/*    if (strcmp(ast->node, ">") == 0)
        return exec_redir_output();
    else if (strcmp(ast->node, ">|") == 0)
        return exec_redir_output();
    else if (strcmp(ast->node, "<") == 0)
        return exec_redir_input();
    else if (strcmp(ast->node, ">>") == 0)
        return exec_redir_appendout();
    else if (strcmp(ast->node, "<<") == 0)
        return exec_redir_heredoc();
    else if (strcmp(ast->node, "<<-") == 0)
        return exec_redir_heredoc();
    else if (strcmp(ast->node, "<&") == 0)
        return exec_redir_dupin();
    else if (strcmp(ast->node, ">&") == 0)
        return exec_redir_dupout();
    else if (strcmp(ast->node, "<>") == 0)
    return exec_redir_rw();*/

    ast = ast;
    return -1;
}
