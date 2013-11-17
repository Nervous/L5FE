#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
# include "../ast/ast.h"

int do_fork(char **argv)
{
    pid_t child;
    int status;
    int ret = 0;
    extern char **environ;

    child = fork();

    if (child != 0)
    {
        ret = waitpid(child, &status, 0);
        free(argv[2]);
        free(argv);
        if (ret == -1)
            return -1;
        else
            return 0;
    }
    else
    {
        if (execve(argv[0], argv, environ) == -1)
            exit(-1);
    }
}

char **build_argv(s_list *ast)
{
    int i = 0;
    int str_size = 0;
    s_list *tmp = ast;

    char **ret = malloc(4 * sizeof (char *));
    ret[0] = "/bin/sh";
    ret[1] = "-c";
    ret[2] = "\0";
    ret[3] = NULL;

    while (ast != NULL)
    {
        str_size += strlen(ast->node->str);
        ret[2] = realloc(ret[2], str_size);
        ret[2] = strcat(ret[2], ast->node->str);
        ast = ast->brothers;
    }

    return ret;
}