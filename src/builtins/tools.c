#include "builtins.h"
#include <unistd.h>

void my_puts(const char *str)
{
    char *buf = NULL;
    buf = malloc(sizeof (char) * strlen(str) + 1);
    int j = 0;
    for (int i = 0; str[i]; i++)
    {
        if (str[i] != '"')
            buf[j++] = str[i];
    }
    buf[j] = '\0';
    write(STDOUT_FILENO, buf, strlen(buf));
    free(buf);
}
