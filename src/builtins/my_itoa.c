#include <string.h>
#include <stdlib.h>

int int_length(int n)
{
    if (n > 0)
    return 1 + int_length(n/10);
    else if (n < 0)
        return 1 +int_length(-n);
    else
        return 0;
}

char *my_reverse_str(const char *src, int op)
{
    int j = 0;
    char *res = NULL;;
    if (!(res = malloc((strlen(src) + 1) * sizeof (char))))
        return NULL;
    int size = strlen(src);

    if (op != -1)
    {
        for (int i = 0; i < size; i++)
        {
            j++;
            res[i] = src[size - j];
        }
    }
    else
    {
        res[0] = '-';
        j++;
        for (int i = 1; i < size; i++)
        {
            j++;
            res[i] = src[size - j];
        }
    }

    res[size] = '\0';
    return res;
}

char *my_itoa(int n)
{
    char *s;
    if (!(s = malloc ((int_length(n) + 1) * sizeof (char))))
        return NULL;
    int i = 0;
    int j = 1;
    int op = 1;
    if (n < 0)
    {
        op = -1;
        n *= -1;
    }
    while ((n / j) != 0)
    {
        s[i] = '0' + ((n / j) % 10);
        j *= 10;
        i++;
    }
        if (op == -1)
        {
            s[i] = '-';
            i++;
        }

        s[i] = '\0';
        return my_reverse_str(s, op);
}
