#ifndef FIFO_H
# define FIFO_H

# include <stdlib.h>
# include <assert.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct list s_list;
struct list
{
  char array[128];
  bool star;
s_list *next;
};

typedef struct fifo
{
  s_list *head;
  s_list *tail;
} s_fifo;

s_fifo *init_fifo(void);
void push(s_fifo *fifo, bool star);
void destroy(s_fifo *fifo);
int compare(s_list *list, const char *str, int i);
void parse(s_fifo *fifo, const char *str);

#endif /* !FIFO_H */
