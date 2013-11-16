#include <stdlib.h>
#include <stdio.h>
#include "utils_error.h"

int parse_error(char *msg)
{
    printf("%s\nExiting ...\n", msg);
    exit(1);
    return -1;
}
