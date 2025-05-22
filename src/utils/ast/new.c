/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:49:36 by tkisaku           #+#    #+#             */
/*   Updated: 2025/05/22 13:50:15 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "libft.h"
#include <stdlib.h>

t_ast *new_pipe_node(t_ast *left, t_ast *right) {
  t_ast *n = malloc(sizeof(t_ast));
  n->type = NODE_PIPE;
  n->argv = NULL;
  n->redirects = NULL;
  n->left = left;
  n->right = right;
  return n;
}

t_ast *new_cmd_node(char **argv, t_redirect *redirs) {
  t_ast *n = malloc(sizeof(t_ast));
  n->type = NODE_CMD;
  n->argv = argv;
  n->redirects = redirs;
  n->left = NULL;
  n->right = NULL;
  return n;
}

t_redirect *new_redirect(char *op, char *file) {
  t_redirect *r = malloc(sizeof(t_redirect));
  r->op = ft_strdup(op);
  r->file = ft_strdup(file);
  r->next = NULL;
  return r;
}
