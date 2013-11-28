#include <stdlib.h>
#include <string.h>
#include "../struct.h"

extern s_global *g_global;

static int tilde_plus(char **str)
{
    char *exp = g_global->current_dir;
    int old_len = strlen(*str);
    int exp_len = strlen(exp);
    int i = 0;
    char *new_str = calloc(old_len + exp_len + 1, sizeof (char));
    for (i = 0; i < exp_len; i++)
    {
        new_str[i] = exp[i];
    }
    for (i = exp_len + 2; i < old_len + exp_len; i++)
    {
        new_str[i - 2] = (*str)[i - exp_len];
    }
    new_str[i - 2] = '\0';
    free(*str);
    *str = new_str;
    return 0;
}

static int tilde_minus(char **str)
{
    char *exp = g_global->previous_dir;
    int old_len = strlen(*str);
    int exp_len = strlen(exp);
    char *new_str = calloc(old_len + exp_len + 1, sizeof (char));
    int i = 0;
    for (i = 0; i < exp_len; i++)
    {
        new_str[i] = exp[i];
    }
    for (i = exp_len + 2; i < old_len + exp_len; i++)
    {
        new_str[i - 2] = (*str)[i - exp_len];
    }
    new_str[i - 2] = '\0';
    free(*str);
    *str = new_str;
    return 0;
}

static int tilde(char **str)
{
    char *exp = getenv("HOME");
    int old_len = strlen(*str);
    int exp_len = strlen(exp);
    char *new_str = calloc(old_len + exp_len + 1, sizeof (char));
    int i = 0;
    for (i = 0; i < exp_len; i++)
    {
        new_str[i] = exp[i];
    }
    for (i = exp_len + 1; i < old_len + exp_len; i++)
    {
        new_str[i - 1] = (*str)[i - exp_len];
    }
    new_str[i - 1] = '\0';
    free(*str);
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
