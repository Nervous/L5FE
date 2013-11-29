#ifndef EXEC_H
# define EXEC_H

# include "string.h"
# include <stdlib.h>
# include "variable.h"
# include "../struct.h"
# include "../ast/ast.h"
# include "../builtins/builtins.h"

/**
** @fn int exec_pipe(s_list *ast);
** @brief Execute the pipe rule
*/
int exec_pipe(s_list *ast);
int exec_funcdec(s_list *funcdec);
/**
** @brief Execute the input rule
*/
int exec_input(s_list *ast);
/**
** @brief Execute the list rule
*/
int exec_list(s_list *ast);
/**
** @brief Execute the command rule
*/
int exec_command(s_list *ast);
/**
** @fn int exec_pipeline(s_list *ast);
** @brief Execute the pipeline rule
*/
int exec_pipeline(s_list *ast);
/**
** @brief Execute the and_or rule
*/
int exec_andor(s_list *ast);
int exec_redir(s_list *redirection);
/**
** @fn int exec_if(s_list *current)
** @brief Execute the "if" rule
*/
int exec_if(s_list *current);
/**
** @fn int exec_else(s_list *current);
** @brief Execute the "else_clause" rule
*/
int exec_else(s_list *current);
/**
** @brief Execute the for rule
*/
int exec_for(s_list *rule_for);
/**
** @brief Execute the while rule
*/
int exec_while(s_list *while_node);
/**
** @brief Execute the until rule
*/
int exec_until(s_list *until);
/**
** @brief Execute the case rule
*/
int exec_case(s_list *rule_case);
int exec_compound(s_list *compound);
/**
** @brief Execute the simple command in current node
*/
int exec_simplecommand(s_list *simple_command);
/**
** @brief Execute the shell command in current node
*/
int exec_shellcommand(s_list *ast);
/**
** @brief Execute the do_group rule
*/
int exec_dogroup(s_list *dogroup);
/**
** @brief Fork the argv given
*/
int do_fork(char **argv);
char **build_argv(s_list *ast);
/**
** @brief Check if the node is a builtin or not
*/
int check_builtin(s_list *ast);
/**
** @brief Execute an alias
*/
int exec_alias(s_list **ast, char *alias_value);
void expand_var(s_list *ast);

#endif /* !EXEC_H */
