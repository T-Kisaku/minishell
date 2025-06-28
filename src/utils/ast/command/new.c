/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:56 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 08:52:56 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_command *new_command(t_cmd_type cmd_type) {
  t_command *new;
  new = malloc(sizeof(t_command));
  if (!new)
    return (NULL);
  new->type = cmd_type;
  new->redir_list = NULL;
  new->u.simple.argc = 0;
  new->u.simple.argv = NULL;
  new->u.simple.token_list = NULL;
  new->u.subshell.and_or_list = NULL;
  return new;
}

t_list *lstnew_command(t_cmd_type cmd_type) {
  t_command *new;
  t_list *new_list;
  new = new_command(cmd_type);
  if (!new)
    return NULL;
  new_list = ft_lstnew((void *)new);
  if (!new_list)
    free(new);
  return new_list;
}

// Return last node of list
t_list *lstadd_back_command(t_list **cmd_list_ptr, t_cmd_type cmd_type) {
  t_list *new_cmd_list;
  new_cmd_list = lstnew_command(cmd_type);
  ft_lstadd_back(cmd_list_ptr, new_cmd_list);
  return new_cmd_list;
}
