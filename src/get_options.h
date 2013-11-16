#ifndef GET_OPTIONS_H
# define GET_OPTIONS_H

# define _GNU_SOURCE
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# include "struct.h"
# include "parser.h"

int get_options(int argc, char **argv);

#endif /* !GET_OPTIONS_H */
