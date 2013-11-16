#ifndef TOKEN_H
# define TOKEN_H

# include <string.h>
# include <ctype.h>
# include "../struct.h"

enum e_type set_token_type(char *str);
int is_separator(char c);


#endif /* !TOKEN_H */
