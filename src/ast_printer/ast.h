#ifndef AST_H
# define AST_H
# include "../struct.h"

s_list *list_copy(s_list *list);
void release_ast(s_list *ast);
void remove_node(s_list *node);
void init_ast(void);
void climb_ast(int height);
void ast_add_step(char *stepName);
void ast_add_node(s_token *token);
s_list *get_root(s_list *current_node);
void test_fill_ast(void);
void print_ast(s_list *ast, const char *filename);
#endif /*!AST_H*/
