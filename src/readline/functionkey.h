#ifndef FUNCTIONKEY_H
# define FUNCTIONKEY_H

typedef void (*callback) (char **b, int *c_p, int *buf_s, int *max_s);

void right_key (char **buf, int *cur_pos, int *buf_size, int *max_size);
void left_key (char **buf, int *cur_pos, int *buf_size, int *max_size);
void backspace (char **buf, int *cur_pos, int *buf_s, int *max_s);
void new_line (char **buf, int *cur_pos, int *buf_size, int *max_size);
void do_nothing (char **buf, int *cur_pos, int *buf_size, int *max_size);

#endif /* !FUNCTIONKEY_H */