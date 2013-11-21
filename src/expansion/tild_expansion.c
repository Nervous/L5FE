#include <stdlib.h>
#include <string.h>

static int tilde_plus(char **str)
{
    char *exp = getenv("PWD");
    int old_len = strlen(*str);
    int exp_len = strlen(exp); //+1 for '\0' which is not counted in strlen
    char *new_str = malloc((old_len + exp_len + 1) * sizeof(char));
    memmove(&(*str[exp_len]), *str, old_len); //makes room for the expansion
    for (int i = 0; i < exp_len; i++)
    {
        new_str[i] = exp[i];
    }
    *str = new_str;
    free(*str);
    return 0;
}

static int tilde_minus(char **str)
{
    char *exp = getenv("PWD"); // A CHANGER PAR APPEL VARIABLE GLOBAL
    int old_len = strlen(*str);
    int exp_len = strlen(exp); //+1 for '\0' which is not counted in strlen
    char *new_str = malloc((old_len + exp_len + 1) * sizeof(char));
    memmove(&(*str[exp_len]), *str, old_len); //makes room for the expansion
    for (int i = 0; i < exp_len; i++)
    {
        new_str[i] = exp[i];
    }
    *str = new_str;
    free(*str);
    return 0;
}

static int tilde(char **str)
{
    char *exp = getenv("HOME");
    int old_len = strlen(*str);
    int exp_len = strlen(exp); //+1 for '\0' which is not counted in strlen
    char *new_str = malloc((old_len + exp_len + 1) * sizeof(char));
    memmove(&(*str[exp_len]), *str, old_len); //makes room for the expansion
    for (int i = 0; i < exp_len; i++)
    {
        new_str[i] = exp[i];
    }
    *str = new_str;
    free(*str);
    return 0;
}

int tilde_handler(char **str)
{
    if (str != NULL && *str != NULL)
    {
        if (*str[1] == '+')
            return tilde_plus(str);
        else if (*str[1] == '-')
            return tilde_minus(str);
        else
            return tilde(str);
    }
    else
        return 1;
}
