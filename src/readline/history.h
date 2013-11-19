#ifndef HISTORY_H
# define HISTORY_H

void init_history(void);
void write_history(void);
char *get_history_ln(void);
void add_to_hist(char *buf);
void free_history(void);

#endif /* !HISTORY_H */
