#include "std.h"

static int get_precedence(int o)
{
    if (o == ADD || o == SUB)
        return 2;
    else if (o == ADD_U || o == SUB_U || o == NOT || o == TILDE)
        return 4;
    else
        return 3;
}

static int keep_going(s_stack *s, int o1)
{
    int o2;
    int p_o1 = 0;

    if (stack_isempty(s) == 0 && stack_top(s)->is_op == 1)
    {
        o2 = stack_top(s)->op;
        p_o1 = get_precedence(o1);
        if ((o1 != ADD_U && o1 != SUB_U && p_o1 == get_precedence(o2))
                || p_o1 < get_precedence(o2))
            return 1;
        else
            return 0;
    }
    return 0;
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


int loop_postfix(s_stack *s, s_queue *out, s_node *act)
{
    out = out;
    while (act != NULL)
    {
        if (act->is_op == 0)
        {
            out = queue_add(out, node_cpy(act));
        }
        else
        {
            while (keep_going(s, act->op) == 1)
            {
                out = queue_add(out, node_cpy(stack_top(s)));
                free(stack_pop(s));
            }
            s = stack_add(s, node_cpy(act));
        }
        act = act->next;
    }

    return 1;
}

s_queue *get_postfix(s_queue *inf)
{
    s_stack *s = NULL;
    s_queue *out = NULL;
    s_node *act = NULL;

    s = s_init();
    out = q_init();
    act = inf->head;

    loop_postfix(s, out, act);

    while (stack_isempty(s) == 0)
    {
        out = queue_add(out, node_cpy(stack_top(s)));
        free(stack_pop(s));
    }

    free_stack(s);
    free_queue(inf);
    return out;
}
