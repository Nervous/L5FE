#include "token.h"

static enum e_type set_type_multiple2(char *str)
{
    if (strcmp(str, "until") == 0)
        return UNTIL;
    if (strcmp(str, "function") == 0)
        return FUNC;
    if (strcmp(str, "||") == 0)
        return PIPE_DOUBLE;
    if (strcmp(str, "&&") == 0)
        return AND_DOUBLE;
    if (strcmp(str, "<<") == 0)
        return TOKEN_REDIR;
    if (strcmp(str, ">>") == 0)
        return TOKEN_REDIR;
    if (strcmp(str, "<<-") == 0)
        return TOKEN_REDIR;
    if (strcmp(str, "<&") == 0)
        return TOKEN_REDIR;
    if (strcmp(str, ">&") == 0)
        return TOKEN_REDIR;
    if (strcmp(str, ">|") == 0)
        return TOKEN_REDIR;
    if (strcmp(str, "<>") == 0)
        return TOKEN_REDIR;
    if (strstr(str, "=") != NULL)
        return ASSIGNMENT_WORD;
    return strcmp(str, ";;") == 0 ? D_SEMICOLON : WORD;
}

static enum e_type set_type_multiple(char *str)
{
    if (strcmp(str, "case") == 0)
        return CASE;
    if (strcmp(str, "esac") == 0)
        return ESAC;
    if (strcmp(str, "do") == 0)
        return DO;
    if (strcmp(str, "done") == 0)
        return DONE;
    if (strcmp(str, "if") == 0)
        return IF;
    if (strcmp(str, "then") == 0)
        return THEN;
    if (strcmp(str, "elif") == 0)
        return ELIF;
    if (strcmp(str, "else") == 0)
        return ELSE;
    if (strcmp(str, "fi") == 0)
        return FI;
    if (strcmp(str, "for") == 0)
        return FOR;
    if (strcmp(str, "in") == 0)
        return IN;
    if (strcmp(str, "while") == 0)
        return WHILE;
    return set_type_multiple2(str);
}

static enum e_type set_type_simple2(char *str)
{
    if (strcmp(str, "<") == 0)
        return TOKEN_REDIR;
    if (strcmp(str, ">") == 0)
        return TOKEN_REDIR;
    if (strcmp(str, ";") == 0)
        return SEMICOLON;
    if (strcmp(str, "\\") == 0)
        return B_SLASH;
    if (strcmp(str, "/") == 0)
        return SLASH;
    if (strcmp(str, "\n") == 0)
        return EOL;
    if (isdigit(*str) != 0)
        return IONUMBER;
    return WORD;
}

static enum e_type set_type_simple(char *str)
{
    if (strcmp(str, "#") == 0)
        return SHARP;
    if (strcmp(str, "!") == 0)
        return NEG;
    if (strcmp(str, "|") == 0)
        return BIT_PIPE;
    if (strcmp(str, "&") == 0)
        return BIT_AND;
    if (strcmp(str, "$") == 0)
        return DOLLAR;
    if (strcmp(str, "\'") == 0)
        return S_QUOTE;
    if (strcmp(str, "\"") == 0)
        return D_QUOTE;
    if (strcmp(str, "`") == 0)
        return B_QUOTE;
    if (strcmp(str, "(") == 0)
        return LEFT_PAR;
    if (strcmp(str, ")") == 0)
        return RIGHT_PAR;
    if (strcmp(str, "{") == 0)
        return LEFT_BRACKET;
    if (strcmp(str, "}") == 0)
        return RIGHT_BRACKET;
    return set_type_simple2(str);
}

enum e_type set_token_type(char *str)
{
    if (strlen(str) == 1)
        return set_type_simple(str);
    else
        return set_type_multiple(str);
}

static int is_separator2(char c)
{
    switch (c)
    {
    case ';':
        return 1;
    case '`':
        return 1;
    case '"':
        return 1;
    case '\'':
        return 1;
    case '#':
        return 1;
    case '<':
        return 1;
    case '>':
        return 1;
    case '\\':
        return 1;
    default:
        return isspace(c);
    }
}

int is_separator(char c)
{
    switch (c)
    {
    case '&':
        return 1;
    case '$':
        return 1;
    case '!':
        return 1;
    case '|':
        return 1;
    case '(':
        return 1;
    case ')':
        return 1;
    case '{':
        return 1;
    case '}':
        return 1;
    default:
        return is_separator2(c);
    }
}
