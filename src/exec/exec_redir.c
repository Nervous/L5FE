#include "exec.h"

int exec_redir(s_list *ast)
{
    switch (ast->brothers->node->str)
    {
    case ">":
        return exec_redir_output(ast);//exec_redir_output();
   /* case ">|":
        return -1;//exec_redir_output();
    case "<":
        return -1;//exec_redir_input();
    case ">>":
        return -1;//exec_redir_appendout();
    case "<<":
        return -1;//exec_redir_heredoc();
    case "<&":
        return -1;//exec_redir_dupin();
    case ">&":
        return -1;//exec_redir_dupout();
    case "<>":
        return -1;//exec_redir_rw();
        default:*/
        return -1;
        //}
}
