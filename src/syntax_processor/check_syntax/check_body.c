/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_body.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 14:18:48 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 14:18:49 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "exit_status.h"
#include "token.h"
#include <stddef.h>

static t_error	*check_syntax_pair(t_token_group cur, t_token_group prev);

t_error	*check_body(t_list **cur, t_list **prev)
{
	t_token_group	cur_group;
	t_token_group	prev_group;
	t_error			*error;

	error = NULL;
	prev_group = lstget_token_group(*prev);
	while (*cur)
	{
		cur_group = lstget_token_group(*cur);
		error = check_syntax_pair(cur_group, prev_group);
		if (error)
			return (error);
		(*prev) = (*cur);
		prev_group = cur_group;
		(*cur) = (*cur)->next;
	}
	return (error);
}

static t_error	*check_syntax_pair(t_token_group cur, t_token_group prev)
{
	t_error	*error;

	error = NULL;
	if (prev == TOKEN_GROUP_REDIR)
	{
		if (cur != TOKEN_GROUP_WORD)
			return (new_error(EXIT_USER_ERR,
					"syntax error: unexpected token after redirection"));
	}
	else if (prev == TOKEN_GROUP_CONTROL_OP)
	{
		if (cur == TOKEN_GROUP_CONTROL_OP)
			return (new_error(EXIT_USER_ERR,
					"syntax error: unexpected token after control operator"));
	}
	return (error);
}
