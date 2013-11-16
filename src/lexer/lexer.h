#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>
# include <stdlib.h>

# include "struct.h"
# include "token.h"

s_token *get_token(enum e_type TYPE);
s_token *eat_token(s_token *tok);

#endif /* !LEXER_H */
