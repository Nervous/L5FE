#ifndef BUILTINS_H
# define BUILTINS_H
# include <stdlib.h>
# include <string.h>
# include "../ast/ast.h"

int my_echo(s_list *ast);
int my_source(s_list *ast);
void my_puts(const char *str);

#endif /*!BUILTINS_H*/
