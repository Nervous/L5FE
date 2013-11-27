#include <stdbool.h>
#include <string.h>
#include "std.h"

static bool fill_char(char *c, const char *old, int size)
{
    char save = *c;
    if (old[0] == '&')
        if (size > 1 && old[1] == '&')
            *c = 'W';
    if (old[0] == '*')
        if (size > 1 && old[1] == '*')
            *c = '?';
    if (old[0] == '|')
        if (size > 1 && old[1] == '|')
            *c = 'K';
    return *c != save;
}

static char *pre_parse(const char *s)
{
    int j = strlen(s);
    int dec = 0;
    char *str = calloc((j + 1), sizeof (char));
    for (int i = 0; i < j; ++i)
    {
        if (!fill_char(str + i, s + i, j - i))
            str[i - dec] = s[i];
        else
        {
            ++dec;
            ++i;
        }
    }
    str = realloc(str, j - dec + 1);
    str[j - dec] = '\0';
    return str;
}

static int get_op2(const char c)
{
    if (c == '&')
        return BIT_AND;
    else if (c == '|')
        return BIT_OR;
    else if (c == 'W')
        return AND;
    else if (c == 'K')
        return OR;
    else if (c == '!')
        return NOT;
    else
        return WHAT;
}

static int get_op(const char c, int *is_op)
{
    if (c == '+')
        return ADD;
    else if (c == '-')
        return SUB;
    else if (c == '*')
        return MULT;
    else if (c == '/')
        return DIV;
    else if (c == '~')
        return TILDE;
    else if (c == '?')
        return POW;
    else if (c == '^')
        return XOR;
    else if (c == ' ')
        return SPACE;
    else if (c >= '0' && c <= '9')
    {
        *is_op = 0;
        return c - 48;
    }
    else
        return get_op2(c);
}

s_node *new(const char c)
{
    s_node *n = NULL;
    int is_op = 1;

    if ((n = malloc(sizeof (s_node))) == NULL)
        return NULL;

    n->op = get_op(c, &is_op);
    n->is_op = is_op;
    n->next = NULL;

    return n;
}

s_node *node_from_int(const int i)
{
    s_node *n = NULL;
    if ((n = malloc (sizeof (s_node))) == NULL)
        return NULL;

    n->op = i;
    n->is_op = 0;
    n->next = NULL;

    return n;
}

void change_unary(s_node *n)
{
    if (n->op == ADD)
        n->op = ADD_U;
    else if (n->op == SUB)
        n->op = SUB_U;
    else if (n->op == TILDE)
        n->op = TILDE;
    else if (n->op == NOT)
        n->op = NOT;
    else
        assert(0 == 1 && "CAN NOT BE UNARY !");
}

static int loop_when_op(s_node *n, int *is_ope, s_queue *q)
{
    if (n->is_op == 1)
    {
        if (n->op == SPACE)
        {
            free(n);
            return 0;
        }
        else if (n->op == WHAT)
            return 1;
        else if (*is_ope == 1)
            change_unary(n);
        else if (*is_ope == 0)
            *is_ope = 1;

        if (n != NULL)
            q = queue_add(q, n);
        if (q == NULL)
            return 4;

        return 0;
    }
    else
        return 1;
}

static int loop_parse(const char *c, int *is_ope, int *acu, s_queue *q)
{
    s_node *n = NULL;
    int ret = 0;
    if (*c >= '0' && *c <= '9')
    {
        *is_ope = 0;
        *acu = *acu * 10 + (*c - 48);
        if (*(c + 1) < '0' || *(c+1) > '9')
        {
            n = node_from_int(*acu);
            q = queue_add(q, n);
            if (q == NULL)
            {
                free(n);
                return 4;
            }
            *acu = 0;
        }
    }
    else
    {
        n = new(*c);
        if (n == NULL)
            return 4;
        ret = loop_when_op(n, is_ope, q);
        if (ret != 0)
        {
            free(n);
            return ret;
        }
    }

    return 0;
}

int parse_eval(const char *s, s_queue *q)
{
    int acu = 0;
    int is_ope = 1;
    int ret = 0;
    char *str = pre_parse(s);

    for (int i = 0; str[i]; ++i)
    {
        ret = loop_parse((str + i), &is_ope, &acu, q);
        if (ret != 0)
            return ret;
    }

    free(str);
    return ret;
}
