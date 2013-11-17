#ifndef VARIABLE_H
# define VARIABLE_H

typedef struct var
{
    char *key;
    char *value;
    struct var *next;
} s_var;

s_var *search_var(s_var *list, char *key);
s_var *add_var(s_var *list, char *key, char *value);
void free_var(s_var *list);
int exec_var(char *str);

#endif /* !VARIABLE_H */
