#ifndef FUNCTION_H
# define FUNCTION_H
# include "../struct.h"

typedef struct function s_function;

struct function
{
    struct list *node;
    char *name;
    s_function *next;
};

void add_function(char *name, struct list *ast);
void free_function(void);
s_function *search_function(char *name);

#endif /* !FUNCTION_H */
