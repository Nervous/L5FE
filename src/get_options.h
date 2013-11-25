#ifndef GET_OPTIONS_H
# define GET_OPTIONS_H

# define _GNU_SOURCE
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# include "struct.h"
# include "parser/parser.h"

int get_options(int argc, char **argv);
int get_file(char *filename, bool config);

#endif /* !GET_OPTIONS_H */
