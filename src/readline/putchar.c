#include <unistd.h>

int my_putchar(int ch)
{
    char c = ch;
    return write(STDOUT_FILENO, &c, 1);
}
