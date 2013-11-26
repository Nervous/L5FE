#include "exec.h"

extern s_global *g_global;

static void expand_param_bra(s_list *ast)
{
    if (ast->brothers->brothers && ast->brothers->brothers->brothers)
    {
        s_var *var = search_var(g_global->var,
                                ast->brothers->brothers->node->str);
        if (var != NULL)
        {
            remove_node(ast->brothers);
            remove_node(ast->brothers);
            remove_node(ast->brothers);
            s_token *tok = malloc(sizeof (s_token));
            char *value = malloc(sizeof (char) * strlen(var->value) + 1);
            value = strcpy(value, var->value);
            tok->str = value;
            free(ast->node->str);
            free(ast->node);
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
            remove_node(ast->brothers);
            s_token *tok = malloc(sizeof (s_token));
            char *value = malloc(sizeof (char) * strlen(var->value) + 1);
            value = strcpy(value, var->value);
            tok->str = value;
            free(ast->node->str);
            free(ast->node);
            ast->node = tok;
        }
    }
}

static void expand_param(s_list *ast)
{
    if (ast->brothers && strcmp(ast->brothers->node->str, "{") == 0)
        expand_param_bra(ast);
    else
        expand_param_nobra(ast);
}

void expand_var(s_list *ast)
{
    if (ast->brothers
        && strcmp(ast->brothers->node->str, "(") == 0)
    {
        if (ast->brothers->brothers
            && strcmp(ast->brothers->brothers->node->str, "(") == 0)
            return; //expend_arith(ast);
        else
            return; //expand_command(ast);
    }
    else
        expand_param(ast);
}
