#include "../arith/arith.h"
#include "../parser/utils_error.h"
#include "../builtins/builtins.h"
#include "exec.h"

extern s_global *g_global;

static void loop_expandarith(int *count, int *other_count, s_list *tmp,
                             s_list *arith_next)
{
    while (*count != 2 && tmp)
    {
        if (strcmp(tmp->node->str, ")") == 0)
        {
            ++(*count);
            tmp = tmp->brothers;
            continue;
        }
        else if (strcmp(tmp->node->str, "$") == 0)
            expand_var(tmp);

        ++(*other_count);
        arith_next->node->str = realloc(arith_next->node->str,
                                        strlen(arith_next->node->str) +
                                        strlen(tmp->node->str) + 1);
        arith_next->node->str = strcat(arith_next->node->str, tmp->node->str);
        tmp = tmp->brothers;
    }

}

static void expand_arith(s_list *ast)
{
    int count = 0;
    int other_count = 0;
    for (int i = 0; i < 2; ++i)
        remove_node(ast->brothers);
    ast->node->str[0] = '\0';
    ast->node->str = realloc(ast->node->str, 2);
    loop_expandarith(&count, &other_count, ast->brothers, ast);

    if (count != 2)
    {
        g_global->file = 1;
        parse_error("Invalid arithmetic expansion");
    }

    int res = evalexpr(ast->node->str);

    for (int i = 0; i < 3 + other_count; ++i)
        remove_node(ast->brothers);
    s_token *tok = malloc(sizeof (s_token));
    if (res == 0)
    {
        tok->str = malloc(2 * sizeof (char));
        tok->str[0] = '0';
        tok->str[1] = '\0';
    }
    else
        tok->str = my_itoa(res);
    free(ast->node->str);
    free(ast->node);
    ast->node = tok;
}

static void expand_param_bra(s_list *ast)
{
    if (ast->brothers->brothers && ast->brothers->brothers->brothers)
    {
        s_var *var = search_var(g_global->var,
                                ast->brothers->brothers->node->str);
        if (var != NULL)
        {
            /* remove nodes '{', '}' and parameter name */
            remove_node(ast->brothers);
            remove_node(ast->brothers);
            remove_node(ast->brothers);
            /* create a new token to update current node ('$') */
            s_token *tok = malloc(sizeof (s_token));
            /* create new string to put into the created token */
            char *value = malloc(sizeof (char) * strlen(var->value) + 1);
            value = strcpy(value, var->value);
            tok->str = value;
            /* free current node token and its corresponding value */
            free(ast->node->str);
            free(ast->node);
            /* assign new token as current node's token */
            ast->node = tok;
        }
    }
}

static void expand_param_nobra(s_list *ast)
{
    if (ast->brothers)
    {
        s_var *var = search_var(g_global->var,
                                ast->brothers->node->str);
        if (var != NULL)
        {
            /* remove node corresponding to parameter name */
            remove_node(ast->brothers);
            /* create a new token to update current node ('$') */
            s_token *tok = malloc(sizeof (s_token));
            /* create new string to put into the created token */
            char *value = malloc(sizeof (char) * strlen(var->value) + 1);
            value = strcpy(value, var->value);
            tok->str = value;
            /* free current node token and its corresponding value */
            free(ast->node->str);
            free(ast->node);
            /* assign new token as current node's token */
            ast->node = tok;
        }
    }
}

static void expand_param(s_list *ast)
{
    if (ast->brothers && strcmp(ast->brothers->node->str, "{") == 0)
        /* parameter is enclosed into brackets */
        expand_param_bra(ast);
    else
        /* parameter is just after '$' */
        expand_param_nobra(ast);
}

/**
** @brief Performs the different expansions needed by the shell.
** Arithmetic expansion, Parameter expansion and commande expansion.
*/

void expand_var(s_list *ast)
{
    if (ast->brothers
        && strcmp(ast->brothers->node->str, "(") == 0)
    {
        /* a '(' follows the '$' */
        if (ast->brothers->brothers
            && strcmp(ast->brothers->brothers->node->str, "(") == 0)
            /* a 2nd '(' follows the '$' hence it's an arithmetic expansion */
            expand_arith(ast);
        else
            /* it's a command expansion */
            return; /* expand_command(ast); */
    }
    else
        /* it's a parameter expansion */
        expand_param(ast);
}
