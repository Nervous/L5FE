#ifndef EVAL_H
# define EVAL_H

# include "std.h"

int parse_eval(const char *s, s_queue *q);
s_queue *get_postfix(s_queue *inf);
s_node *node_from_int(const int i);
int eval(s_queue *pos, int *result);

#endif /* !EVAL_H */
