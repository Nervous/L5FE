#include "builtins.h"
#include <unistd.h>

void my_puts(const char *str)
{
    write(STDOUT_FILENO, str, strlen(str));
}
