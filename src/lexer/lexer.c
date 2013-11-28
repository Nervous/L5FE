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

static char *create_comment(char *str, unsigned int i)
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
        char *value = malloc(sizeof (char) * i + 1);
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

    unsigned int len = strlen(++str);

    while (i < len && !(str[i] == str[0]
                        && (str[i - 1] != '\\' || str[0] == '\'')))
        i++;

    if (i == len && str[i] != str[0])
    {
        char *value = malloc(sizeof (char) * 9);
        strncpy(value, "!@#*()%^", 8);
        value[8] = '\0';
        g_global->pos += i;
        return value;
    }
    else
    {
        i++;
        char *value = malloc(sizeof (char) * i + 1);
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

    if ((i - pos - 1) != 4294967295 && (str[i - pos - 1] == '=')
        && (str[i - pos] == '"'))
    {
        i++;
        while (i < len && (str[i++ - pos] != '"' || str[i - pos - 2] == '\\'))
            ;
    }

    if ((i - pos) == 0 && ((is_separator(str[0]) == 1
                            && isspace(str[0]) == 0) || str[0] == '\n'))
        return special_separator(str);

    g_global->pos = i;
    value = malloc(sizeof (char) * (i - pos) + 1);
    strncpy(value, str, (i - pos));
    value[i - pos] = '\0';
    return value;
}

static char *remove_backslash(char *str)
{
    if (str[0] == '"' || str[0] == '\'')
        return str;

    int count = 0;
    for (unsigned int i = 0; i < strlen(str); i++)
        if (str[i] == '\\')
            count++;

    if (count != 0)
    {
        char *s = calloc(strlen(str) + 1, sizeof(char));
        char *save = str;
        while (str[0])
        {
            if (str[0] == '"')
                while ((++str)[0] != '"')
                    s = strncat(s, str - 1, 1);
            if ((str++)[0] != '\\'
                || ((str - 1)[0] == '\\' && str[0] == '\\' && str++))
                s = strncat(s, str - 1, 1);
        }
        free(save);
        return s;
    }

    return str;
}

/**
** @brief Checks if the current token is no a special delimiter when the parser
** calls for a WORD token
*/

static enum e_type is_expected(enum e_type type)
{
    if (type == EOL || type == E_EOF || type == BIT_PIPE || type == BIT_AND
        || type == SEMICOLON || type == TOKEN_REDIR || type == PIPE_DOUBLE
        || type == AND_DOUBLE)
        return type;
    return WORD;
}

s_token *get_token(enum e_type expected)
{
    s_token *token;
    char *str = g_global->readline;

    if ((token = malloc(sizeof (s_token))) == NULL)
        printf("Error when creating token\n");

    find_next_token(str);

    token->pos = g_global->pos;
    token->str = set_token_value(str, token->pos);
    token->str = remove_backslash(token->str);

    token->type = set_token_type(token->str);
    if (strlen(token->str) == 0)
        token->type = E_EOF;
    else if (token->str[strlen(token->str) - 1] == '=')
        token->str[strlen(token->str) - 1] = '\0';

    if (expected == WORD)
        token->type = is_expected(token->type);
    else if (token->str[0] == '#')
    {
        free(token->str);
        free(token);
        return get_token(expected);
    }

    if (strcmp(token->str, "!@#*()%^") == 0)
        token->type = ERROR;

    return token;
}

s_token *eat_token(s_token *tok)
{
    if (tok == NULL)
        return NULL;
    if (strlen(tok->str) > 0 && strcmp(tok->str, "\n") != 0
        && strcmp(tok->str, "fi") != 0 && strcmp(tok->str, "done") != 0)
    {
        ast_add_node(tok);
    }

    free(tok->str);
    free(tok);
    return NULL;
}
