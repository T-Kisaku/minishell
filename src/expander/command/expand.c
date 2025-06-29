/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:59 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 08:52:59 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "error.h"
#include "expander.h"
#include "minishell.h"
#include "token.h"

static t_error	*expand_token_list(t_list **tokens, t_minishell_state *shell);

t_error	*expand_handler(t_command *cmd, t_minishell_state *shell)
{
	t_error	*error;

	error = NULL;
	if (cmd->type == CMD_SIMPLE)
	{
		error = expand_token_list(&cmd->u.simple.token_list, shell);
		if (is_error(error))
			return (error);
	}
	else if (cmd->type == CMD_SUBSHELL)
	{
		error = expand_ast(cmd->u.subshell.and_or_list, shell);
		if (is_error(error))
			return (error);
	}
	return (error);
}

static t_error	*expand_token_list(t_list **tokens, t_minishell_state *shell)
{
	t_list	*cur_token;
	t_token	*cur_token_content;
	t_error	*error;

	error = NULL;
	cur_token = *tokens;
	while (cur_token)
	{
		cur_token_content = (t_token *)cur_token->content;
		if (cur_token_content->type == TOKEN_UNQUOTED_WORD
			|| cur_token_content->type == TOKEN_DOUBLE_QUOTED_WORD)
		{
			error = expand_single_token(cur_token->content, shell);
			if (is_error(error))
				return (error);
		}
		cur_token = cur_token->next;
	}
	return (error);
}
