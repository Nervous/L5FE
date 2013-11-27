#ifndef FUNCTIONKEY_H
# define FUNCTIONKEY_H

typedef void (*f_callback) (char **b, int *c_p, int *buf_s, int *max_s);

/**
** @brief These functions define the actions made by key sequences.
*/
void right_key(char **buf, int *cur_pos, int *buf_size, int *max_size);
void left_key(char **buf, int *cur_pos, int *buf_size, int *max_size);
void down_key(char **buf, int *cur_pos, int *buf_size, int *max_size);
void up_key(char **buf, int *cur_pos, int *buf_size, int *max_size);
void backspace(char **buf, int *cur_pos, int *buf_s, int *max_s);
void delete(char **buf_p, int *cur_pos, int *buf_size, int *max_size);
void new_line(char **buf, int *cur_pos, int *buf_size, int *max_size);
void do_nothing(char **buf, int *cur_pos, int *buf_size, int *max_size);
void ctrl_a(char **buf_p, int *cur_pos, int *buf_s, int *max_s);
void ctrl_e(char **buf_p, int *cur_pos, int *buf_s, int *max_s);
void ctrl_l(char **buf_p, int *cur_pos, int *buf_s, int *max_s);
void delete_end(char **buf_p, int *cur_pos, int *buf_size, int *max_size);

#endif /* !FUNCTIONKEY_H */
