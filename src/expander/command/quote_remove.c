/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_remove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:59 by tkisaku           #+#    #+#             */
/*   Updated: 2025/07/04 10:51:37 by saueda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static t_error	*process_simple(t_list *head);

t_error	*quote_removal_handler(t_command *cmd, t_minishell_state *shell)
{
	t_error	*error;

	(void)shell;
	error = NULL;
	if (cmd->type == CMD_SIMPLE)
	{
		error = process_simple(cmd->u.simple.token_list);
		if (is_error(error))
			return (error);
	}
	return (error);
}

static t_error	*process_simple(t_list *head)
{
	t_list	*cur;
	t_token	*cur_token_content;
	t_error	*error;

	error = NULL;
	cur = head;
	while (cur)
	{
		cur_token_content = (t_token *)cur->content;
		if (cur_token_content->type == TOKEN_UNQUOTED_WORD)
		{
			error = quote_remove_core(cur_token_content);
			if (is_error(error))
				return (error);
		}
		cur = cur->next;
	}
	return (NULL);
}
