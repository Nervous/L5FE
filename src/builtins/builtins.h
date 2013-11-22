#ifndef BUILTINS_H
# define BUILTINS_H
# include <stdlib.h>
# include <string.h>
# include "../ast/ast.h"

int my_cd(s_list *ast);
int my_echo(s_list *ast);
int my_source(s_list *ast);
void my_puts(const char *str);
void exit_builtin(int n);
int my_alias(s_list *ast);
int my_unalias(s_list *ast);
int my_export(s_list *ast);
int my_shopt(s_list *ast);
int my_history(s_list *ast);

#endif /*!BUILTINS_H*/
