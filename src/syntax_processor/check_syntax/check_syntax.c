/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:57 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 14:19:12 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "exit_status.h"
#include "minishell.h"
#include "syntax_processor.h"
#include "syntax_processor/check_syntax.h"
#include "token.h"
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>

static t_error	*check_head(t_list **cur, t_list **prev);

t_error	*check_syntax(t_list **list, t_minishell_state *shell)
{
	t_error	*error;
	t_list	*cur;
	t_list	*prev;

	if (!list)
		return (new_error(EXIT_INTERNAL_ERR, "list is NULL"));
	cur = *list;
	prev = NULL;
	error = check_head(&cur, &prev);
	if (is_error(error))
		return (error);
	error = check_body(&cur, &prev);
	if (is_error(error))
		return (error);
	return (check_tail(list, shell));
}

static t_error	*check_head(t_list **cur, t_list **prev)
{
	if (lstget_token_group(*cur) == TOKEN_GROUP_CONTROL_OP)
		return (new_error(EXIT_USER_ERR,
				"syntax error: unexpected token at the beginning"));
	(*prev) = (*cur);
	(*cur) = (*cur)->next;
	return (NULL);
}
