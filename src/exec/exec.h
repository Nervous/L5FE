#ifndef EXEC_H
# define EXEC_H

# include <stdlib.h>
# include "../struct.h"
# include "../ast/ast.h"

int exec_if(s_list *rule_if);
int exec_compount(s_list *compound);

#endif /* !EXEC_H */
