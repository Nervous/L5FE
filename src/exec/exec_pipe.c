#include "exec.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include "../ast/ast.h"

static int son_pipe(s_list *ast, int fdlist[2], char **environ)
{
    char **argv = NULL;
    close(fdlist[1]);
    dup2(fdlist[0], STDIN_FILENO);
    int ret = 0;
    if (ast->brothers->brothers->brothers)
        ret = exec_pipe(ast->brothers->brothers);
    else
    {
        s_list *tmp = ast->brothers->brothers->son_list;
        argv = build_argv(tmp->son_list);
        if ((ret = execve(argv[0], argv, environ)) == -1)
            exit(-1);
    }
    return ret;
}

static int father_pipe(int pid, int fdlist[2], int *status, char **argv)
{
    close(fdlist[0]);
    waitpid(pid, status, 0);
    close(fdlist[1]);
    if (argv)
    {
        free(argv[2]);
        free(argv);
    }

    if (!WIFEXITED(*status))
        return -1;
    return 0;
}

/**
** @fn int exec_pipe(s_list *ast);
** @brief Execute the pipe rule
*/
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
            if ((ret = execve(argv[0], argv, environ)) == -1)
                exit(-1);
        }
        else
            ret = father_pipe(pid, fdlist, &status, argv);
    }
    return ret;
}
