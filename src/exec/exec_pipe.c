#include "exec.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
# include "../ast/ast.h"

/*int exec_pipe(s_list *ast)
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
}*/
int exec_pipe(s_list *ast)
{
    int fdlist[2]; //0 is read size, 1 is write
    int ret = 0;
    int pid = 0;
    int status;
    char **argv = NULL;
    extern char **environ;
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
            argv = build_argv(tmp->son_list);
            ret = execve(argv[0], argv, environ);
        }
    }
    else //else father
    {
        pid = fork();
        if (!pid)
        {
            close(fdlist[0]);
            dup2(fdlist[1], STDOUT_FILENO);
            argv = build_argv(ast->son_list->son_list);
            ret = execve(argv[0], argv, environ);
        }
        else
        {
            close(fdlist[0]);
            waitpid(pid, &status, 0);
            close(fdlist[1]);
            if (argv)
            {
                free(argv[2]);
                free(argv);
            }

            if (!WIFEXITED(status))
                return -1;
        }
    }
    return ret;
}
