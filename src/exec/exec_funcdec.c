#include "exec.h"
#include "function.h"
void add_function(char *name, struct list *ast);

int exec_funcdec(struct list *funcdec)
{
    while (funcdec->brothers && strcmp(funcdec->brothers->node->str, "(") != 0)
        funcdec = funcdec->brothers;
    char *name = funcdec->node->str;
    while (funcdec->brothers)
        funcdec = funcdec->brothers;
    add_function(name, funcdec);

    return 0;
}
