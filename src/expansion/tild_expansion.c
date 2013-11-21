#include <stdlib.h>
#include <string.h>

int tilde_plus(char **str)
{
    char *exp = getenv("PWD");
    int old_len = strlen(*str);
    int exp_len = strlen(exp); //+1 for '\0' which is not counted in strlen
    *str = realloc(*str, (old_len + exp_len + 1) * sizeof(char));
    memmove(&(*str[exp_len]), *str, old_len); //makes room for the expansion
    for (int i = 0; i < exp_len; i++)
    {
        *str[i] = exp[i];
    }
    return 0;
}

int tilde_handler(char **str)
{
    if (str != NULL && *str != NULL)
    {
        if (str[1] == '+')
            return tilde_plus(str);
        else if (str[1] == '-')
            return tilde_plus(str);
        else
            return tilde_plus(str);
    }
    else
        return 1;
}
