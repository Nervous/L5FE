#include "../arith/arith.h"
#include "../parser/utils_error.h"
#include "../builtins/builtins.h"
#include "exec.h"

extern s_global *g_global;

static void expand_arith(s_list *ast)
{
    s_list *arith_next = ast->brothers->brothers->brothers->brothers;
    if (arith_next && strcmp(arith_next->node->str, ")") == 0 &&
            arith_next->brothers &&
            strcmp(arith_next->brothers->node->str, ")") == 0)
    {
        int res = evalexpr(ast->brothers->brothers->brothers->node->str);
        /* remove node corresponding to parameter name */
        remove_node(ast->brothers);

        remove_node(ast->brothers->brothers);
        remove_node(ast->brothers->brothers->brothers);
        remove_node(arith_next);
        remove_node(arith_next->brothers);
        /* create a new token to update current node ('$') */
        s_token *tok = malloc(sizeof (s_token));
        /* create new string to put into the created token */
        tok->str = my_itoa(res);
        /* free current node token and its corresponding value */
        free(ast->node->str);
        free(ast->node);
        /* assign new token as current node's token */
        ast->node = tok;
    }
    else
    {
        g_global->file = 1;
        parse_error("Invalid arithmetic expansion");
    }
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
