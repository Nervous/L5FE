#ifndef BUILTINS_H
# define BUILTINS_H
# include <stdlib.h>
# include <string.h>
# include "../ast/ast.h"

typedef struct options
{
    char *name;
    int activated;
} s_options;

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
int modify_opt(char *name, int activate);
char *my_itoa(int n);

#endif /*!BUILTINS_H*/
