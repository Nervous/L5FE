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

/**
** @brief Parses the argument passed to 42sh to find the options. If no
** argument is provided, 42sh will run in interactive mode
*/
int get_options(int argc, char **argv);

/**
** @brief Reads the file passed as an argument to 42sh and stores it into a
** single single to parse and execute
*/
int get_file(char *filename, bool config);

#endif /* !GET_OPTIONS_H */
