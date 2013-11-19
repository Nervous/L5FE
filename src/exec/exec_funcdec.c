#include "exec.h"
#include "function.h"

int exec_funcdec(s_list *funcdec)
{
    while (funcdec->brothers && strcmp(funcdec->brothers->node->str, "(") != 0)
        funcdec = funcdec->brothers;
    char *name = funcdec->node->str;
    while (funcdec->brothers)
        funcdec = funcdec->brothers;
    add_function(name, funcdec);

    return -1;
}
