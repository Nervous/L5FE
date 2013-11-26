#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../ast/ast.h"
#include "exec.h"

static void do_checkredir(int *spaces, int redir)
{
    if (*spaces != 0 || redir == 0)
        return;
    *spaces = redir;
}

static void is_redirection(s_list *ast, int *spaces)
{
    int redir = 0;
    if (ast->brothers && strcmp(ast->brothers->node->str, ">") == 0)
        redir = 1;
    else if (ast->brothers && strcmp(ast->brothers->node->str, "<") == 0)
        redir = 1;
    else if (ast->brothers && strcmp(ast->brothers->node->str, ">>") == 0)
        redir = 2;
    else if (ast->brothers && strcmp(ast->brothers->node->str, "<<") == 0)
        redir = 2;
    else if (ast->brothers && strcmp(ast->brothers->node->str, "<<-") == 0)
        redir = 3;
    else if (ast->brothers && strcmp(ast->brothers->node->str, ">&") == 0)
        redir = 2;
    else if (ast->brothers && strcmp(ast->brothers->node->str, "<&") == 0)
        redir = 2;
    else if (ast->brothers && strcmp(ast->brothers->node->str, ">|") == 0)
        redir = 2;
    else if (ast->brothers && strcmp(ast->brothers->node->str, "<>") == 0)
        redir = 2;
    do_checkredir(spaces, redir);
}

int do_fork(char **argv)
{
    if (!argv)
        return 0;
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
    int str_size = 1;
    int spaces = 0;
    char **ret = malloc(4 * sizeof (char *));
    ret[0] = "/bin/sh";
    ret[1] = "-c";
    ret[2] = malloc(sizeof (char));
    ret[2][0] = '\0';
    ret[3] = NULL;

    while (ast != NULL)
    {
        if (strcmp(ast->node->str, "$") == 0)
            expand_var(ast);
        str_size += strlen(ast->node->str);
        if (ast->brothers != NULL)
            str_size += 1;
        ret[2] = realloc(ret[2], str_size);
        ret[2] = strcat(ret[2], ast->node->str);
        is_redirection(ast, &spaces);
        if (ast->brothers != NULL && spaces == 0)
            ret[2] = strcat(ret[2], " ");
        else
            spaces = spaces == 0 ? 0 : spaces - 1;
        ast = ast->brothers;
    }

    return ret;
}
