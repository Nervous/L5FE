#include "exec.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "../ast/ast.h"

int exec_redir_output(s_list *ast)
{
    int pid = 0;
    int status;
    extern char **environ;
    int fd = 0;
    int fd2 = 0;
    pid = fork();

    if (pid != 0)
    {
        waitpid(child, &status, 0);
        close(fd2);
        free(argv[2]);
        free(argv);

        if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
            return 0;
        else
            return -1;
    }
    else
    {
        argv = build_argv(ast);
        fd = open(argv[2], O_RDONLY);
        fd2 = open(argv[0], O_RDONLY);
        dup2(fd, fd2);
        execve(argv[0], argv, environ);
        close(fd);
    }
}
