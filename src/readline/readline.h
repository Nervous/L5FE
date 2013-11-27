#ifndef READLINE_H
# define READLINE_H

/**
** @brief This function is responsible of setting up the terminal and
** the termcap database
*/
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
