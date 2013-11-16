#ifndef EXEC_H
# define EXEC_H

# include <stdlib.h>
# include "../struct.h"
# include "../ast/ast.h"

int exec_if(s_list *rule_if);
int exec_compount(s_list *compound);
int exec_simplecommand(s_list *simple_command);
int do_fork(char **argv);
char **build_argv(s_list *ast);

#endif /* !EXEC_H */
