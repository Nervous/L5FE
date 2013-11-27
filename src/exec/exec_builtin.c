#include "exec.h"
#include "../builtins/builtins.h"
#include <string.h>
#include "exec.h"
#include <stdio.h>
extern s_global *g_global;

static int check_builtin3(s_list *ast)
{
    if (strcmp(ast->node->str, "alias") == 0)
        my_alias(ast->brothers);
    else if (strcmp(ast->node->str, "unalias") == 0)
        my_unalias(ast->brothers);
    else if (strcmp(ast->node->str, "export") == 0)
        my_export(ast->brothers);
    else if (strcmp(ast->node->str, "shopt") == 0)
        my_shopt(ast->brothers);
    else if (strcmp(ast->node->str, "history") == 0)
        my_history(ast->brothers);
    else
        return -1;
    return 0;
}

static int check_builtin2(s_list *ast)
{
    if (strcmp(ast->node->str, "break") == 0)
    {
        if (ast->brothers)
            g_global->break_nb = atoi(ast->brothers->node->str);
        else
            g_global->break_nb = 1;
        return 0;
    }
    else if (strcmp(ast->node->str, "continue") == 0)
    {
        if (ast->brothers)
            g_global->continue_nb = 1;
        else
            g_global->continue_nb = 1;
        return 0;
    }
    else if (strcmp(ast->node->str, "cd") == 0)
    {
        my_cd(ast->brothers);
        return 0;
    }
    else
        return check_builtin3(ast);
}

int check_builtin(s_list *ast)
{
    if (!ast)
        return -1;
    if (strcmp(ast->node->str, "echo") == 0)
    {
        my_echo(ast->brothers);
        return 0;
    }
    else if (strcmp(ast->node->str, "source") == 0
             || strcmp(ast->node->str, ".") == 0)
    {
        my_source(ast->brothers);
        return 0;
    }
    else if (strcmp(ast->node->str, "exit") == 0)
    {
        if (ast->brothers)
            exit_builtin(atoi(ast->brothers->node->str));
        else
            exit_builtin(g_global->ret);
        return 0;
    }
    else
        return check_builtin2(ast);
}

static s_list *create_alias_token(s_list *father, s_list *new_ast, char *value)
{
    s_list *ret = new_ast;
    while (new_ast && new_ast->brothers)
        new_ast = new_ast->brothers;

    s_token *token = NULL;
    token = malloc(sizeof (s_token));
    token->str = value;
    token->type = WORD;

    s_list *new_node = NULL;
    new_node = malloc(sizeof (s_list));
    new_node->node = token;
    new_node->father = father;
    new_node->son_list = NULL;
    new_node->brothers = NULL;

    if (new_ast)
        new_ast->brothers = new_node;
    else
        ret = new_node;

    return ret;
}

int exec_alias(s_list **ast, char *str)
{
    s_list *father = (*ast)->father;
    s_list *new_ast = NULL;
    char *alias_value = malloc(sizeof (char) * strlen(str) + 1);
    strcpy(alias_value, str);

    alias_value++;
    int len = strlen(alias_value) - 1;
    int i = 0;

    while (i < len)
    {
        while (i < len && alias_value[i] && alias_value[i] != ' ')
            i++;
        alias_value[i++] = '\0';

        char *value = malloc(sizeof (char) * strlen(alias_value) + 1);
        strcpy(value, alias_value);
        value[i - 1] = '\0';
        for (int j = 0; j < i; j++)
            alias_value++;
        i = 0;
        len = strlen(alias_value) - 1;

        new_ast = create_alias_token(father, new_ast, value);
    }

    new_ast->father = father;
    remove_node(*ast);

    return exec_simplecommand(new_ast);
}
