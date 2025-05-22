/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:49:41 by tkisaku           #+#    #+#             */
/*   Updated: 2025/05/22 13:50:04 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include <stdlib.h>

static void free_redirects(t_redirect *r) {
  t_redirect *next;
  while (r) {
    next = r->next;
    free(r->op);
    free(r->file);
    free(r);
    r = next;
  }
}

void free_ast(t_ast *node) {
  size_t i;

  if (!node)
    return;

  free_ast(node->left);
  free_ast(node->right);

  if (node->argv) {
    for (i = 0; node->argv[i]; ++i) {
      free(node->argv[i]);
    }
    free(node->argv);
  }

  free_redirects(node->redirects);

  free(node);
  node = NULL;
}
