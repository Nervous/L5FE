#include <stdio.h>
#include <stdlib.h>
#include "../struct.h"
#include "../ast/ast.h"
#include "lexer.h"

extern s_global *g_global;

/**
** @brief Find the position of the beginning of the next token
*/

static void find_next_token(char *s)
{
    unsigned int len = strlen(s);

      while (g_global->pos < len
             && (s[g_global->pos] == ' ' || s[g_global->pos] == '\t'))
      g_global->pos += 1;
}

/**
** @brief Creates a new malloc'ed string which will serve as the token value and
*/

static char *create_special_string(char *str, int nb)
{
    char *value = malloc(sizeof (char) * nb + 1);
    value = strncpy(value, str, nb);
    value[nb] = '\0';
    g_global->pos += nb;

    return value;
}

/**
** @brief Creates a token which will be interpreted as a comment and will not
** be parsed.
*/

char *create_comment(char *str, unsigned int i)
{
    if (str[0] == '$' || str[0] == '\\')
    {
        str++;
        char *value = malloc(sizeof (char) * 2);
        strncpy(value, str, 1);
        value[1] = '\0';
        g_global->pos += 1;

        return value;
    }
    else
    {
        str++;
        unsigned int len = strlen(str);

        while (i < len && str[i] != '\n')
            i++;
        char *value = malloc(sizeof (char) * i);
        strncpy(value, str, i);
        value[i] = '\0';
        g_global->pos += i;

        return value;
    }
}

/**
** @brief Create a token which begins with a quoting character
*/

static char *create_quote_token(char *str)
{
    unsigned int i = 1;

    if (str[1] == '#')
        return create_comment(str, i);

    str++;
    unsigned int len = strlen(str);

    while (i < len && !(str[i] == str[0]
                        && (str[i - 1] != '\\' || str[0] == '\'')))
        i++;

    if (i == len && str[i] != str[0])
        printf("Lexer error, unable to find corresponding %c\n", str[0]);
    else
        {
            i++;
            char *value = malloc(sizeof (char) * i);
            strncpy(value, str, i);
            value[i] = '\0';
            g_global->pos += i;

            return value;
        }

    return "";
}

/**
** @brief Tests if the value of the token is a special parameter such as '|',
** '&', '<', '>' or ';' and create the appropriate string tu put as the token
** value
*/

static char *special_separator(char *str)
{
    if (strlen(str) > 1 && (str[0] == '&' || str[0] == '|' || str[0] == '>'
                            || str[0] == '<' || str[0] == ';')
        && str[0] == str[1])
        {
            if (strlen(str) > 2 && str[0] == '<'
                && str[2] == '-')
                return create_special_string(str, 3);
            else
                return create_special_string(str, 2);
        }
    else if (strlen(str) > 1)
        {
            if (strncmp(str, "<&", 2) == 0)
                return create_special_string(str, 2);
            else if (strncmp(str, ">&", 2) == 0)
                return create_special_string(str, 2);
            else if (strncmp(str, "<>", 2) == 0)
                return create_special_string(str, 2);
            else if (strncmp(str, ">|", 2) == 0)
                return create_special_string(str, 2);
        }

    if (str[0] == '"' || str[0] == '`' || str[0] == '\'' || str[0] == '#')
        return create_quote_token(--str);

    return create_special_string(str, 1);
}

/**
** @brief Returns the new malloc'ed string which will serve as the nex token
** value
*/

static char *set_token_value(char *str, unsigned int pos)
{
    char *value;
    unsigned int i = 0;
    unsigned int len = strlen(str);

    while (i < pos)
        {
            i++;
            str++;
        }

    while (i < len && is_separator(str[i - pos]) == 0)
        i++;

    if ((i - pos) == 0
        && ((is_separator(str[0]) == 1
             && isspace(str[0]) == 0) || str[0] == '\n'))
        return special_separator(str);

    g_global->pos = i;
    value = malloc(sizeof (char) * (i - pos) + 1);
    strncpy(value, str, (i - pos));
    value[i - pos] = '\0';
    return value;
}

/**
** @brief Checks if the current token is no a special delimiter when the parser
** calls for a WORD token
*/

static enum e_type is_expected(enum e_type type)
{
    if (type == EOL || type == E_EOF || type == BIT_PIPE || type == BIT_AND
        || type == SEMICOLON || type == TOKEN_REDIR || type == PIPE_DOUBLE
        || type == AND_DOUBLE || type == RIGHT_BRACKET || type == RIGHT_PAR)
        return type;
    return WORD;
}

/**
** @brief Analyzes lexically the input str and returns the next token it has
** recognized. If the parser explicitely called for a WORD token, a WORD token
** should be recognized only if recognized token's type is not a special
** delimiter determined by is_expected()
*/

s_token *get_token(enum e_type expected)
{
    s_token *token;
    char *str = g_global->readline;

    if ((token = malloc(sizeof (s_token))) == NULL)
        printf("Error when creating token\n");

    find_next_token(str);

    token->pos = g_global->pos;
    token->str = set_token_value(str, token->pos);
    token->type = set_token_type(token->str);
    token->son_list = NULL;
    if (strlen(token->str) == 0)
        token->type = E_EOF;

    if (expected == WORD)
        token->type = is_expected(token->type);
    else if (token->str[0] == '#')
    {
        free(token->str);
        free(token);
        return get_token(expected);
    }

    //DEBUG & TESTING
    //printf("New token created:\nTYPE = %d\nSTR = %s\n\n",
    //token->type, token->str);


    return token;
}

s_token *eat_token(s_token *tok)
{
    if (strlen(tok->str) > 0 && strcmp(tok->str, "\n") != 0
        && strcmp(tok->str, "fi") != 0 && strcmp(tok->str, "done") != 0)
    {
        ast_add_node(tok);
    }

    free(tok->str);
    free(tok);
    return NULL;
}
