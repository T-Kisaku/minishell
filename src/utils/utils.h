

#ifndef UTILS_H
#define UTILS_H

#include <stddef.h> //size_t
#include <stdbool.h>
#include "libft.h" //t_list
#include "ast.h"   //t_ast, t_command
#include "error.h"

// free_ast_1.c
void free_ast(t_ast **ast);
void del_and_or(void *content);
void free_command_list(t_list **command_list);
void del_command(void *content);
void free_command(t_command **cmd);

// free_ast_2.c
void free_redir_list(t_list **head);
void del_redir(void *content);
void free_token_list(t_list **head);
void del_token_content(void *content);
void free_argv(char ***argv, int num);

char *ft_strndup(const char *s, size_t n);

void free_and_null(void **ptr);

t_error *cmd_loop(t_ast *ast, t_error *(*handler)(t_command *));
t_error *redir_loop(t_ast *ast, t_error *(*handler)(t_redir *));

// write_error.c
int write_error(char *msg);
int syntax_error(const char *token);

#endif
