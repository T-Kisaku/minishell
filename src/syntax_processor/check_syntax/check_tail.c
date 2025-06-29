/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tail.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 14:19:21 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 14:19:21 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "exit_status.h"
#include "ft_list.h"
#include "minishell.h"
#include "syntax_processor.h"
#include "token.h"
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>

static t_error	*check_control_op_tail(t_list *tail, t_minishell_state *shell);
static t_error	*append_token(char *input, t_list *tail,
					t_minishell_state *shell);

t_error	*check_tail(t_list **list, t_minishell_state *shell)
{
	t_token_group	group;
	t_list			*tail;

	tail = ft_lstlast(*list);
	if (!tail)
		return (new_error(EXIT_INTERNAL_ERR, "list is empty"));
	group = lstget_token_group(tail);
	if (group == TOKEN_GROUP_CONTROL_OP)
		return (check_control_op_tail(tail, shell));
	else if (group == TOKEN_GROUP_REDIR)
		return (new_error(EXIT_USER_ERR,
				"syntax error: unexpected token at the end of input"));
	else if (group == TOKEN_GROUP_WORD)
		return (NULL);
	else
		return (new_error(EXIT_INTERNAL_ERR,
				"syntax error: token group not set"));
}

// TODO: this should handle unclosed quote as well in the future
static t_error	*check_control_op_tail(t_list *tail, t_minishell_state *shell)
{
	char	*input;
	t_error	*error;

	if (shell->is_interactive != 0)
		return (new_error(EXIT_USER_ERR,
				"syntax error: you need to close last token bro!"));
	while (1)
	{
		input = readline("> ");
		if (!input)
			return (new_error(EXIT_EOF, "exit"));
		else if (!*input)
		{
			free(input);
			continue ;
		}
		error = append_token(input, tail, shell);
		free(input);
		return (error);
	}
}

static t_error	*append_token(char *input, t_list *tail,
		t_minishell_state *shell)
{
	t_error	*error;
	t_list	*new_token;

	new_token = NULL;
	error = str_to_token(input, &new_token);
	if (is_error(error))
	{
		if (new_token)
			lstclear_token(&new_token);
		return (error);
	}
	error = check_syntax(&new_token, shell);
	if (is_error(error))
	{
		if (new_token)
			lstclear_token(&new_token);
		return (error);
	}
	tail->next = new_token;
	return (NULL);
}
