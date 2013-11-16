#include <stdlib.h>
#include <stdio.h>
#include "utils_error.h"

void parse_error(char *msg)
{
    printf("%s\nExiting ...", msg);
    exit(1);
}
