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
#include "builtins/builtins.h"
#include "arith/arith.h"

s_global *g_global = NULL;

static void init_options(void)
{
    g_global->options[0] = malloc(sizeof (s_options));
    g_global->options[0]->name = "ast_print";
    g_global->options[0]->activated = 0;
    g_global->options[1] = malloc(sizeof (s_options));
    g_global->options[1]->name = "dotglob";
    g_global->options[1]->activated = 0;
    g_global->options[2] = malloc(sizeof (s_options));
    g_global->options[2]->name = "expand_aliases";
    g_global->options[2]->activated = 0;
    g_global->options[3] = malloc(sizeof (s_options));
    g_global->options[3]->name = "extglob";
    g_global->options[3]->activated = 0;
    g_global->options[4] = malloc(sizeof (s_options));
    g_global->options[4]->name = "nocaseglob";
    g_global->options[4]->activated = 0;
    g_global->options[5] = malloc(sizeof (s_options));
    g_global->options[5]->name = "nullglob";
    g_global->options[5]->activated = 0;
    g_global->options[6] = malloc(sizeof (s_options));
    g_global->options[6]->name = "sourcepath";
    g_global->options[6]->activated = 0;
    g_global->options[7] = malloc(sizeof (s_options));
    g_global->options[7]->name = "xpg_echo";
    g_global->options[7]->activated = 0;
}
void init_global2(void)
{
    g_global->pos = 0;
    g_global->ast = 0;
    g_global->file = 0;
    g_global->norc = 0;
    g_global->ret = 0;
    g_global->break_nb = 0;
    g_global->continue_nb = 0;
    g_global->arith = 0;
}

void init_global(void)
{
    if (!(g_global = malloc(sizeof (s_global))))
        return;
    init_global2();
    g_global->current_node = NULL;
    g_global->last_node_id = 0;
    g_global->readline = NULL;
    g_global->hist_file = NULL;
    g_global->hist_arr = NULL;
    g_global->var = NULL;
    g_global->func = NULL;
    g_global->alias_list = NULL;
    init_options();
    g_global->current_dir = malloc(sizeof (char) * 128);
    g_global->previous_dir = malloc(sizeof (char) * 128);
    g_global->current_dir = getcwd(g_global->current_dir, 128);
    g_global->previous_dir = strcpy(g_global->previous_dir,
                                    g_global->current_dir);
    g_global->x_pos = 0;
    g_global->y_pos = 0;
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
    for (int i = 0; i < 8; i++)
        free(g_global->options[i]);
    free(g_global);
}

int main(int argc, char **argv)
{
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
