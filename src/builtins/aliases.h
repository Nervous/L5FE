#ifndef ALIASES_H
# define ALIASES_H

typedef struct alias
{
    char *name;
    char *value;
    struct alias *next;
} s_alias;

char *alias_get_value(char *name);
int alias_set_value(char *name, char *value);
void add_alias(char *name, char *value);
void unalias(char *name);
void free_alias_list(void);

#endif /*!ALIASES_H*/
