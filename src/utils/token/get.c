/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:56 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 13:12:20 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include <stdbool.h>
#include <stddef.h>

t_token	*lstget_token(t_list *node)
{
	if (!node || !node->content)
		return (NULL);
	return ((t_token *)node->content);
}


t_token_group lstget_token_group(t_list *node)
{
  t_token_type type;
	if (!node || !node->content)
    return TOKEN_GROUP_WORD;
  type = lstget_token(node)->type;
  if(is_redir_token(type))
    return TOKEN_GROUP_REDIR;
  else if(is_control_op_token(type))
    return TOKEN_GROUP_CONTROL_OP;
  return TOKEN_GROUP_WORD;
}
