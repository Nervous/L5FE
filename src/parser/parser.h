#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "struct.h"
# include "../lexer/lexer.h"
# include "utils_string.h"
# include "utils_error.h"
# include "ast/ast.h"

int parse(void);

int parse_andor(s_token **tok, bool mandatory);
int parse_pipeline(s_token **tok, bool mandatory);
int parse_prefix(s_token **tok);
int parse_element(s_token **tok);
int parse_redirection(s_token **tok);
int parse_compoundlist(s_token **tok, bool mandatory);
int parse_shellcommand(s_token **tok);
int parse_function(s_token **tok);

int parse_rulefor(s_token **tok);
int parse_rulewhile(s_token **tok);
int parse_ruleuntil(s_token **tok);
int parse_rulecase(s_token **tok);
int parse_ruleif(s_token **tok);

void parse_loop_EOL(s_token **tok);
void parse_loop_WORD(s_token **tok);

#endif
