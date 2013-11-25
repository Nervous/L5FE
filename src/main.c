#include <stdlib.h>
#include "builtins/aliases.h"
#include "parser/parser.h"
#include "ast/ast.h"
#include "lexer/lexer.h"
#include "struct.h"
#include "parser/parser.h"
#include "get_options.h"
#include "exec/exec.h"
#include "readline/history.h"

#include "arith/arith.h"

s_global *g_global = NULL;

void init_global(void)
{
    if (!(g_global = malloc(sizeof (s_global))))
        return;
    g_global->current_node = NULL;
    g_global->last_node_id = 0;
    g_global->pos = 0;
    g_global->ast = 0;
    g_global->file = 0;
    g_global->norc = 0;
    g_global->ret = 0;
    g_global->break_nb = 0;
    g_global->continue_nb = 0;
    g_global->readline = NULL;
    g_global->hist_file = NULL;
    g_global->hist_arr = NULL;
    g_global->var = NULL;
    g_global->func = NULL;
    g_global->current_dir = malloc(sizeof (char) * 128);
    g_global->previous_dir = malloc(sizeof (char) * 128);
    g_global->current_dir = getcwd(g_global->current_dir, 128);
    g_global->previous_dir = strcpy(g_global->previous_dir,
                                    g_global->current_dir);
}

void free_global(void)
{
    free(g_global->readline);
    release_ast(get_root(g_global->current_node));
    free_alias_list();
    free(g_global->current_node);
    if (g_global->hist_file)
        free(g_global->hist_file);
    free_var(g_global->var);
    free_function();
    if (g_global->hist_arr)
        free_history();
    free(g_global->current_dir);
    free(g_global->previous_dir);
    free(g_global);
}

void test_arith(char *str)
{
    printf("**** RESULT OF EVAL : \n\t%d\n*********************\n\n", evalexpr("~1"));
    exit(42);
}

int main(int argc, char **argv)
{
    if (argc == 3 && argv[1][0] == 'q') // RM ME
        test_arith(argv[2]); // PLEASE RM ME DONT FORGET OMG FMDASJDNJASND

    atexit(free_global);
    init_global();

    int ret = get_options(argc, argv);
    ret = exec_input(get_root(g_global->current_node));

    if (g_global->ast)
        print_ast(get_root(g_global->current_node), "tree.dot");
    release_ast(get_root(g_global->current_node));

    if (ret == -1)
        ret = 1;

    return ret;
}
