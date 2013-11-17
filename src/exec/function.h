#ifndef FUNCTION_H
# define FUNCTION_H

# include "../struct.h"

typedef struct function s_function;

struct function
{
    s_list *node;
    char *name;
    s_function *next;
};

#endif /* !FUNCTION_H */
