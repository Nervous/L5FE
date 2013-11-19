#include "exec.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include "../ast/ast.h"

int son_pipe(s_list *ast, int fdlist[2], char **environ)
{
    char **argv = NULL;
    close(fdlist[1]);
    dup2(fdlist[0], STDIN_FILENO);
    if (ast->brothers->brothers->brothers)
        exec_pipe(ast->brothers->brothers);
    else
    {
        s_list *tmp = ast->brothers->brothers->son_list;
        argv = build_argv(tmp->son_list);
        return execve(argv[0], argv, environ);
    }
    return 0;
}
int exec_pipe(s_list *ast)
{
    int fdlist[2];
    int ret = 0;
    int pid = 0;
    int status;
    char **argv = NULL;
    extern char **environ;
    pipe(fdlist);
    pid = fork();
    if (!pid)
        ret = son_pipe(ast, fdlist, environ);
    else
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
