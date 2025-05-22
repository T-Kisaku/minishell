/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:01:58 by tkisaku           #+#    #+#             */
/*   Updated: 2025/05/22 13:50:37 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H

#define AST_H

typedef enum e_node_type {
  NODE_CMD,
  NODE_PIPE,
  NODE_AND,
  NODE_OR,
  NODE_SUBSHELL
} t_node_type;

// op: operation of redirects. ex) <, >, <<, >>
typedef struct s_redirect {
  char *op;
  char *file;
  struct s_redirect *next;
} t_redirect;

/*
 * # How to execute with this struct
 * - When type is NODE_CMD use argv/redirects
 * - When type is not NODE_CMD use left and right
 *
 * # Warnings
 * - argv should have NULL at the end of it ex) ["echo", "fire", NULL]
 */
typedef struct s_ast {
  t_node_type type;
  char **argv;
  t_redirect *redirects;
  struct s_ast *left;
  struct s_ast *right;
} t_ast;

void free_ast(t_ast *node);
t_ast *new_cmd_node(char **argv, t_redirect *redirs);
t_ast *new_pipe_node(t_ast *left, t_ast *right);
t_redirect *new_redirect(char *op, char *file);

#endif // !AST_H
