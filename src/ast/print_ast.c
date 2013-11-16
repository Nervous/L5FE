#include <stdlib.h>
#include <stdio.h>
#include "../struct.h"
#include "ast.h"

extern s_global *g_global;

static void print_node_text(s_list *ast, FILE *f)
{
    fprintf(f, "%u", ast->father->id);
    fprintf(f, "->");
    fprintf(f, "%u", ast->id);
    fprintf(f, "\n");
    fprintf(f, "%u [label = \"%s\"]",
        ast->father->id, ast->father->node->str);
    fprintf(f, "\n");
    fprintf(f, "%u [label = \"%s\"]", ast->id, ast->node->str);
    fprintf(f, "\n");
}
static void print_node(s_list *ast, FILE *f)
{
    s_list *tmp = ast;
    if (!tmp)
        return;
    if (!tmp->node->son_list)
        print_node_text(ast, f);
    while (tmp->node->son_list)
    {
        if (tmp->father && tmp->linked == 0)
        {
            print_node_text(tmp, f);
            tmp->linked = 1;
        }
        print_node(tmp->node->son_list, f);
        tmp->node->son_list = tmp->node->son_list->brothers;
    }
//    free(ast);
}

void print_ast(s_list *ast, const char *fileName)
{
    FILE *f;
    if (!ast)
        return;
    if (!(f = fopen(fileName, "w")))
        return;
    fprintf(f, "digraph ast\n");
    fprintf(f, "{");
    fprintf(f, "\n");
    print_node(ast, f);
    fprintf(f, "}");
    fclose(f);
}

void climb_ast(int height)
{
    for (int i = 0; i < height; i++)
    {
        if (g_global->current_node->father)
            g_global->current_node = g_global->current_node->father;
    }
}
