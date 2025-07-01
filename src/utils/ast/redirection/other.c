/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:56 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 08:52:56 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include <stddef.h>

t_redir	*lstget_redir(t_list *node)
{
	if (!node || !node->content)
		return (NULL);
	return ((t_redir *)node->content);
}

t_redir_type	get_redir_type(t_token_type token_type)
{
	if (token_type == TOKEN_REDIR_INPUT)
		return (REDIR_INPUT);
	if (token_type == TOKEN_REDIR_OUTPUT)
		return (REDIR_OUTPUT);
	if (token_type == TOKEN_REDIR_HERE_DOC)
		return (REDIR_HERE_DOC);
	if (token_type == TOKEN_REDIR_APPEND)
		return (REDIR_APPEND);
	return (REDIR_INPUT);
}
