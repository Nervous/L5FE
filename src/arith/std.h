#ifndef STD_H
# define STD_H

# include <stdlib.h>
# include <unistd.h>
# include <assert.h>

enum operat
{
    ADD_U,
    SUB_U,
    ADD,
    SUB,
    MULT,
    DIV,
    POW,
    XOR,
    BIT_AND,
    BIT_OR,
    AND,
    OR,
    NOT,
    TILDE,
    SPACE,
    WHAT
};

struct node
{
    int op;
    int is_op;
    struct node *next;
};

typedef struct node s_node;

struct queue
{
    s_node *head;
    s_node *tail;
};

typedef struct queue s_queue;
s_queue *q_init(void);
s_queue *queue_add(s_queue *q, s_node *n);
void free_queue(s_queue *q);

struct stack
{
    s_node *head;
};

typedef struct stack s_stack;

s_stack *s_init(void);
s_stack *stack_add(s_stack *s, s_node *n);
s_node *stack_pop(s_stack *s);
s_node *stack_top(s_stack *s);
int stack_isempty(s_stack *s);
int stack_size(s_stack *s);
void free_stack(s_stack *s);

#endif
