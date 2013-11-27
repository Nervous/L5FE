#include "parser.h"

extern s_global *g_global;
static int parse_simplecommand(s_token **tok)
{
    ast_add_step("Simple_command");

    if (parse_prefix(tok) == -1)
    {
        if (parse_element(tok) == -1)
        {
            remove_node(g_global->current_node);
            return -1;
        }

        while (parse_element(tok) == 0)
            ;

        return 0;
    }

    while (parse_prefix(tok) == 0)
        ;

    while (parse_element(tok) == 0)
        ;

    climb_ast(1);
    return 0;
}

static int parse_command(s_token **tok)
{
    ast_add_step("Command");
    if (parse_simplecommand(tok) == 0)
    {
        climb_ast(1);
        return 0;
    }
    else if (parse_shellcommand(tok) == 0)
    {
        while (parse_redirection(tok) == 0)
            ;
        climb_ast(1);
        return 0;
    }
    else if (parse_function(tok) != 0)
    {
        remove_node(g_global->current_node);
        return -1;
    }
    return 0;
}

static void parse_orcommand(s_token **tok)
{
    while (true)
    {
        if ((*tok)->type != BIT_PIPE)
            return;
        climb_ast(1);
        *tok = eat_token(*tok);
        *tok = get_token(PIPELINE);
        climb_ast(1);
        parse_loop_EOL(tok);
        if (parse_command(tok) == -1)
            parse_error("PARSE ERROR : Was expecting a command");
    }
}


int parse_pipeline(s_token **tok, bool mandatory)
{
    ast_add_step("Pipeline");
    if ((*tok)->type == NEG)
    {
        *tok = eat_token(*tok);
        *tok = get_token(PIPELINE);
        climb_ast(1);
    }

    if (parse_command(tok) == -1)
    {
        if (mandatory)
            parse_error("PARSE ERROR : Was expecting a command");
        else
        {
            remove_node(g_global->current_node);
            return -1;
        }
    }
    parse_orcommand(tok);
    climb_ast(1);
    return 0;
}
