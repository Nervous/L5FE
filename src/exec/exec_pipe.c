#include "exec.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
# include "../ast/ast.h"

int exec_pipe(s_list *ast)
{
    int fdlist[2]; //0 is read size, 1 is write
    int ret = 0;
    int pid = 0;
    pipe(fdlist); //1) Pipe
    pid = fork(); //2) Fork
    if (!pid) //if 0 then we are in the son
    {
        close(fdlist[1]); //close write side
        dup2(fdlist[0], STDIN_FILENO); //dup STDIN
        if (ast->brothers->brothers->brothers) //if multiples pipes
            exec_pipe(ast->brothers->brothers);
        else //exec cmd
        {
            s_list *tmp = ast->brothers->brothers->son_list;
            ret = do_fork(build_argv(tmp->son_list));
        }
    }
    else //else father
    {
        close(fdlist[0]);
        dup2(fdlist[1], STDOUT_FILENO);
        ret = do_fork(build_argv(ast->son_list->son_list));
    }
    return ret;
}
