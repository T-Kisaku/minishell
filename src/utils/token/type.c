/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 16:04:10 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 16:04:11 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include <stdbool.h>
#include <stddef.h>

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
