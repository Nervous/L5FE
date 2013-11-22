#include "builtins.h"
#include "../struct.h"

extern s_global *g_global;

void exit_builtin(int n)
{
    if (n == -1)
        exit(1);
    else
        exit(n);
}
