#include "parser.h"
#include "ast/ast.h"
#include "lexer.h"
#include "struct.h"
#include "parser.h"
#include "get_options.h"

s_global *g_global = NULL;

void init_global(void)
{
    if (!(g_global = malloc(sizeof (s_global))))
        return;
    g_global->current_node = NULL;
    g_global->last_node_id = 0;
    g_global->pos = 0;
    g_global->ast = 0;
    g_global->norc = 0;
    g_global->readline = NULL;
}


int main(int argc, char **argv)
{
    init_global();

    int ret = get_options(argc, argv);

    if (g_global->ast)
        print_ast(get_root(g_global->current_node), "test.dot");
    else
        release_ast(get_root(g_global->current_node));
    return ret;
}
