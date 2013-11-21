#include <stdlib.h>
#include <string.h>

int tilde_plus(char **str)
{
    char *exp = getenv("PWD");
    int old_len = strlen(*str);
    int exp_len = strlen(exp); //+1 for '\0' which is not counted in strlen
    *str = realloc(*str, (old_len + exp_len + 1) * sizeof(char));
    
}

int tilde_handler(char **str)
{
    if (str != NULL && *str != NULL)
    {
        if (str[1] == '+')
            return tilde_plus(str);
        else if (str[1] == '-')
            return tilde_minus(str);
        else
            return tilde(str);
    }
    else
        return 1;
}
