#ifndef EXEC_H
# define EXEC_H

# include <stdlib.h>
# include "../struct.h"
# include "../ast/ast.h"

int exec_input(s_list *ast);
int exec_list(s_list *ast);
int exec_command(s_list *ast);
int exec_pipeline(s_list *ast)
int exec_andor(s_list *ast)
int exec_if(s_list *rule_if);
int exec_compound(s_list *compound);
int exec_simplecommand(s_list *simple_command);
int exec_dogroup(s_list *dogroup);
int do_fork(char **argv);
char **build_argv(s_list *ast);

#endif /* !EXEC_H */
