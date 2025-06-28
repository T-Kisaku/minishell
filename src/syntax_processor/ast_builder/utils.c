/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:57 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 08:52:57 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h> //bool,
#include "ast.h"
#include "error.h"
#include "exit_status.h"
#include "libft.h"
#include "syntax_processor/ast_builder.h"

t_error *advance_token(t_list **token_list_ptr) {
  if (!token_list_ptr || !*token_list_ptr)
    return (
        new_error(EXIT_INTERNAL_ERR, "not good args for advance_token bro!!"));
  *token_list_ptr = (*token_list_ptr)->next;
  return NULL;
}

t_and_or *get_last_and_or(t_list **and_or_list_ptr) {
  t_list *last_andor_node;
  if (!and_or_list_ptr)
    return NULL;
  if (!*and_or_list_ptr)
    *and_or_list_ptr = lstnew_and_or(OP_NONE);
  last_andor_node = ft_lstlast(*and_or_list_ptr);
  if (last_andor_node == NULL)
    lstget_and_or(lstadd_back_and_or(and_or_list_ptr, OP_NONE));
  return lstget_and_or(last_andor_node);
}

t_command *get_last_cmd(t_list **and_or_list_ptr) {
  t_and_or *last_and_or;
  t_list *last_cmd_node;
  last_and_or = get_last_and_or(and_or_list_ptr);
  if (!last_and_or) // TODO: error handling
    return NULL;
  last_cmd_node = ft_lstlast(last_and_or->pipeline->command_list);
  if (last_cmd_node == NULL)
    return lstget_command(
        lstadd_back_command(&last_and_or->pipeline->command_list, CMD_SIMPLE));
  return lstget_command(last_cmd_node);
}
