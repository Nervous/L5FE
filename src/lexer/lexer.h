#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>
# include <stdlib.h>

# include "../struct.h"
# include "token.h"

/**
** @brief Analyzes lexically the input str and returns the next token it has
** recognized. If the parser explicitely called for a WORD token, a WORD token
** should be recognized only if recognized token's type is not a special
** delimiter determined by is_expected()
*/
s_token *get_token(enum e_type TYPE);

s_token *eat_token(s_token *tok);

#endif /* !LEXER_H */
