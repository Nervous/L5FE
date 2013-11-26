#include <stdlib.h>
#include <string.h>
#include "../struct.h"

extern s_global *g_global;

static int tilde_plus(char **str)
{
    char *exp = g_global->current_dir;
    int old_len = strlen(*str);
    int exp_len = strlen(exp); //+1 for '\0' which is not counted in strlen
    char *new_str = "\0";
    new_str = calloc(old_len + exp_len + 1,  sizeof(char));
    //memmove(&((*str)[exp_len]), *str, old_len); //makes room for the expansion
    for (int i = exp_len; i < old_len + exp_len; i++)
    {
        new_str[i] = *str[i - exp_len];
    }
    for (int i = 0; i < exp_len; i++)
    {
        new_str[i] = exp[i];
    }
    //free(*str);
    *str = new_str;
    return 0;
}

static int tilde_minus(char **str)
{
    char *exp = g_global->previous_dir; // A CHANGER PAR APPEL VARIABLE GLOBAL
    int old_len = strlen(*str);
    int exp_len = strlen(exp); //+1 for '\0' which is not counted in strlen
    char *new_str = malloc((old_len + exp_len + 1) * sizeof(char));
    memmove(&((*str)[exp_len]), *str, old_len); //makes room for the expansion
    for (int i = 0; i < exp_len; i++)
    {
        new_str[i] = exp[i];
    }
    //free(*str);
    *str = new_str;
    return 0;
}

static int tilde(char **str)
{
    char *exp = getenv("HOME");
    int old_len = strlen(*str);
    int exp_len = strlen(exp); //+1 for '\0' which is not counted in strlen
    char *new_str = malloc((old_len + exp_len + 1) * sizeof(char));
    memmove(&((*str)[exp_len]), *str, old_len); //makes room for the expansion
    for (int i = 0; i < exp_len; i++)
    {
        new_str[i] = exp[i];
    }
    //free(*str);
    *str = new_str;
    return 0;
}

int tilde_handler(char **str)
{
    if (str != NULL && *str != NULL)
    {
        if ((*str)[0] == '~')
        {
            if ((*str)[1] == '+')
                return tilde_plus(str);
            else if ((*str)[1] == '-')
                return tilde_minus(str);
            else
                return tilde(str);
        }
        else
            return 1;
    }
    else
        return 1;
}
