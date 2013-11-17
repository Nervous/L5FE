#ifndef EXEC_H
# define EXEC_H

# include <stdlib.h>
# include "../struct.h"
# include "../ast/ast.h"

int exec_if(s_list *current);
int exec_compound(s_list *compound);
int exec_simplecommand(s_list *simple_command);
int exec_dogroup(s_list *dogroup);
int exec_ruleuntil(s_list *until):
int do_fork(char **argv);
char **build_argv(s_list *ast);

#endif /* !EXEC_H */
