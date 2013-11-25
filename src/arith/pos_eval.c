#include <math.h>
#include "eval.h"

static int make_2(int what, int v1, int v2, int *err)
{
    if (what == DIV)
    {
        if (v1 == 0)
        {
            *err = 3;
            return 0;
        }
        return v2 / v1;
    }
    else if (what == POW)
        return v1 + v2; /* POW V2 V1 */
    else if (what == XOR)
        return v2 ^ v1;
    else if (what == BIT_AND)
        return v2 & v1;
    else if (what == BIT_OR)
        return v2 | v1;
    else if (what == AND)
        return v2 && v1;
    else if (what == OR)
        return v2 || v1;
    else
        *err = 1;
    return 0;
}
static int make(int what, int v1, int v2, int *err)
{
    if (what == ADD)
        return v1 + v2;
    else if (what == SUB)
        return v2 - v1;
    else if (what == ADD_U)
        return v1;
    else if (what == SUB_U)
        return -v1;
    else if (what == NOT)
        return !v1;
    else if (what == MULT)
        return v1 * v2;
    else
        return make_2(what, v1, v2, err);
}


static s_node *node_cpy(const s_node *n)
{
    s_node *new = NULL;
    assert(n != NULL);

    if ((new = malloc(sizeof (s_node))) == NULL)
        return NULL;

    new->op = n->op;
    new->is_op = n->is_op;
    new->next = NULL;

    return new;
}


static int loop_eval(s_node *act, s_stack *s, s_node *v1, int *res)
{
    s_node *v2 = NULL;
    int vv2 = 0;
    int err = 0;

    if (act->is_op == 0)
    {

        if ((s = stack_add(s, node_cpy(act))) == NULL)
            return 4;
    }
    else
    {
        if (stack_size(s) < 1)
            return 4;
        v1 = stack_pop(s);
        if (act->op != ADD_U && act->op != SUB_U)
        {
            if (stack_size(s) < 1)
                return 2;
            v2 = stack_pop(s);
            assert(v2 != NULL);
            vv2 = v2->op;
        }

        *res = make(act->op, v1->op, vv2, &err);
        if (err != 0)
            return err;
        stack_add(s, node_from_int(*res));
        free(v1);
        free(v2);
    }
    act = act->next;

    return 0;
}

int eval(s_queue *pos, int *result)
{
    s_node *act = NULL;
    s_stack *s = NULL;
    s_node *v1 = NULL;
    int err = 0;

    if (pos == NULL)
        return 4;

    if ((s = s_init()) == NULL)
        return 4;

    act = pos->head;
    while (act != NULL)
    {
        err = loop_eval(act, s, v1, result);
        if (err != 0)
            return err;

        act = act->next;
    }

    if (stack_size(s) != 1)
        return 1;

    v1 = stack_pop(s);
    *result = v1->op;
    free(v1);
    free_stack(s);
    return 0;
}
