#include "std.h"

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
        return R_PAR;
    else if (c == ' ')
        return SPACE;
    else if (c >= '0' && c <= '9')
    {
        *is_op = 0;
        return c - 48;
    }
    else
        return WHAT;
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
        else if (*is_ope == 1 && (n->op != L_PAR))
            change_unary(n);
        else if (*is_ope == 0 && (n->op == L_PAR))
            return 2;
        else if (*is_ope == 1 && (n->op == R_PAR))
            return 2;
        else if (*is_ope == 0 && (n->op != R_PAR))
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

int parse(const char *s, s_queue *q)
{
    int acu = 0;
    int is_ope = 1;
    int ret = 0;

    for (int i = 0; s[i]; ++i)
    {
        ret = loop_parse((s + i), &is_ope, &acu, q);
        if (ret != 0)
            return ret;
    }
    return ret;
}
