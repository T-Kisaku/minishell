/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:56 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 08:52:56 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"
#include <stdbool.h>
#include <stddef.h>

t_token	*lstget_token(t_list *node)
{
	if (!node || !node->content)
		return (NULL);
	return ((t_token *)node->content);
}

bool	is_word_token(t_token_type type)
{
	return (type == TOKEN_UNQUOTED_WORD || type == TOKEN_SINGLE_QUOTED_WORD
		|| type == TOKEN_DOUBLE_QUOTED_WORD);
}

bool	is_redir_token(t_token_type type)
{
	return (type == TOKEN_REDIR_INPUT || type == TOKEN_REDIR_OUTPUT
		|| type == TOKEN_REDIR_HERE_DOC || type == TOKEN_REDIR_HERE_STRINGS
		|| type == TOKEN_REDIR_APPEND);
}

bool	is_control_op_token(t_token_type type)
{
	return (type == TOKEN_PIPE || type == TOKEN_AND_IF || type == TOKEN_OR_IF);
}
