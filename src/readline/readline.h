#ifndef READLINE_H
# define READLINE_H

void readline(void);
void write_buf(char *buf, int cur_pos, int buf_size);
void write_ps(void);
int my_putchar(int ch);
void add_char(void);

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
