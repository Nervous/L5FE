#ifndef FN_MATCH_H
# define FN_MATCH_H
# include <stdlib.h>

struct node
{
    int array_char[128];
    char is_star;
    struct node *next;
};
typedef struct node s_node;

struct queue
{
    s_node  *head;
    s_node  *tail;
};
typedef struct queue s_queue;

s_queue *init_queue(void);
int add_queue(s_queue *queue, int boolean);
void free_queue_match(s_queue *queue);

int parser(s_queue *queue, const char *str);
int match(s_node *node, const char *str);

#endif /* !FN_MATCH_H */
