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

/**
**@brief cd builtin, allow the user to change the directory
*/
int my_cd(s_list *ast);
/**
**@brief echo builtin, allow the user to print a message
*/
int my_echo(s_list *ast);
/**
**@brief source builtin, execute a file given in argument
*/
int my_source(s_list *ast);
/**
**@brief Write a string on STDOUT
*/
void my_puts(const char *str);
/**
**@brief exit builtin, exit the 42sh
*/
void exit_builtin(int n);
/**
**@brief alias builtin, set a new alias given in argument
*/
int my_alias(s_list *ast);
/**
**@brief unalias builtin, unset an existing alias
*/
int my_unalias(s_list *ast);
/**
**@brief export builtin, export a global variable
*/
int my_export(s_list *ast);
/**
**@brief shopt builtin, display a list of options of 42sh
*/
int my_shopt(s_list *ast);
/**
**@brief history builtin, display the history file
*/
int my_history(s_list *ast);
/**
**@brief Modify an option from the shopt options
*/
int modify_opt(char *name, int activate);
/**
**@brief Convert an int to a string
*/
char *my_itoa(int n);

#endif /*!BUILTINS_H*/
