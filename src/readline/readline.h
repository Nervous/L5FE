#ifndef READLINE_H
# define READLINE_H

void readline(void);
void write_buf(char *buf, int cur_pos, int buf_size);

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
