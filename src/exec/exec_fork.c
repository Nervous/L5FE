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
    extern char **environ;

    child = fork();

    if (child != 0)
    {
        waitpid(child, &status, 0);
        free(argv[2]);
        free(argv);

        if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
            return 0;
        else
            return -1;
    }
    else
    {
        if (execve(argv[0], argv, environ) == -1)
            exit(-1);
        return -1;
    }
}

char **build_argv(s_list *ast)
{
    int str_size = 0;
    char **ret = malloc(4 * sizeof (char *));
    ret[0] = "/bin/sh";
    ret[1] = "-c";
    ret[2] = malloc(sizeof (char));
    ret[2][0] = '\0';
    ret[3] = NULL;

    while (ast != NULL)
    {
        str_size += strlen(ast->node->str);
        if (ast->brothers != NULL)
            str_size += 1;
        ret[2] = realloc(ret[2], str_size);
        ret[2] = strcat(ret[2], ast->node->str);
        if (ast->brothers != NULL)
            ret[2] = strcat(ret[2], " ");
        ast = ast->brothers;
    }

    return ret;
}
