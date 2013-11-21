#ifndef EXEC_H
# define EXEC_H

# include "string.h"
# include <stdlib.h>
# include "variable.h"
# include "../struct.h"
# include "../ast/ast.h"

int exec_pipe(s_list *ast);
int exec_funcdec(s_list *funcdec);
int exec_input(s_list *ast);
int exec_list(s_list *ast);
int exec_command(s_list *ast);
int exec_pipeline(s_list *ast);
int exec_andor(s_list *ast);
int exec_redir(s_list *redirection);
int exec_if(s_list *current);
int exec_else(s_list *current);
int exec_for(s_list *rule_for);
int exec_while(s_list *while_node);
int exec_until(s_list *until);
int exec_case(s_list *rule_case);
int exec_compound(s_list *compound);
int exec_simplecommand(s_list *simple_command);
int exec_shellcommand(s_list *ast);
int exec_dogroup(s_list *dogroup);
int exec_ruleuntil(s_list *until);
int do_fork(char **argv);
char **build_argv(s_list *ast);
int check_builtin(s_list *ast);

#endif /* !EXEC_H */
