#ifndef READLINE_H
# define READLINE_H

void readline(void);

typedef enum key
{
    LEFT,
    RIGHT,
    UP,
    DOWN,
    BACKSPACE,
    DEL,
    RL
} e_key;


#endif /* !READLINE_H */
