#ifndef AST_H
# define AST_H
# include "../struct.h"

s_list *list_copy(s_list *list);
/**
** @fn void release_ast(s_list *ast)
** @brief Free all the nodes of the AST
*/
void release_ast(s_list *ast);
/**
** @fn void remove_node(s_list *node)
** @brief Remove a node in the AST
*/
void remove_node(s_list *node);
void init_ast(void);
/*
** @fn void climb_ast(int height);
** @brief Set the current node to its father
*/
void climb_ast(int height);
/**
** @fn void ast_add_step(char *stepName)
** @brief Add a new abstract son to the current node
*/
void ast_add_step(char *stepName);
/**
** @fn void ast_add_node(s_token *token);
** @brief Add a son to the current node
*/
void ast_add_node(s_token *token);
/**
**@fn s_list *get_root(s_list *current_node);
**@brief Returns the root of the AST
*/
s_list *get_root(s_list *current_node);
void test_fill_ast(void);
/**
** @fn void print_ast(s_list *ast, const char *fileName);
** @brief Print the whole AST and store it in a .dot file
*/
void print_ast(s_list *ast, const char *filename);
/**
** @fn s_token *copy_token(s_token *token);
** @brief Copy the token given in parameter in a new token
*/
s_token *copy_token(s_token *token);

#endif /*!AST_H*/
