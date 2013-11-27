#ifndef ALIASES_H
# define ALIASES_H

typedef struct alias
{
    char *name;
    char *value;
    struct alias *next;
} s_alias;

/**
** @brief Return the value of an alias whose name is given in parameter
*/
char *alias_get_value(char *name);

/**
** @brief Set the value of an alias whose name is given in parameter
*/
int alias_set_value(char *name, char *value);
/**
** @brief Add a new alias in the alias list
*/
void add_alias(char *name, char *value);
/**
** @brief Remove an alias from the aliast list
*/
void unalias(char *name);
/**
** @brief Free the alias list
*/
void free_alias_list(void);

#endif /*!ALIASES_H*/
