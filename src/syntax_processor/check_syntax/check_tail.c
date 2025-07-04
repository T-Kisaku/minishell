/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tail.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 14:19:21 by tkisaku           #+#    #+#             */
/*   Updated: 2025/07/03 11:53:27 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "exit_status.h"
#include "ft_list.h"
#include "libft.h"
#include "minishell.h"
#include "syntax_processor.h"
#include "syntax_processor/check_quote.h"
#include "token.h"
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>

static t_error	*check_control_op_tail(t_list *tail, char **original_input,
					t_minishell_state *shell);
static t_error	*append_token(char **input, t_list *tail,
					t_minishell_state *shell);
static t_error	*append_input(char *new_input, char **original_input);

t_error	*check_tail(t_list **list, char **original_input,
		t_minishell_state *shell)
{
	t_token_group	group;
	t_list			*tail;

	tail = ft_lstlast(*list);
	if (!tail)
		return (new_error(EXIT_INTERNAL_ERR, "list is empty"));
	group = lstget_token_group(tail);
	if (group == TOKEN_GROUP_CONTROL_OP)
		return (check_control_op_tail(tail, original_input, shell));
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
static t_error	*check_control_op_tail(t_list *tail, char **original_input,
		t_minishell_state *shell)
{
	char	*new_input;
	t_error	*error;

	if (!shell->is_interactive)
		return (new_error(EXIT_USER_ERR,
				"syntax error: you need to close last token bro!"));
	while (1)
	{
		new_input = readline("> ");
		if (!new_input)
			return (new_error(EXIT_EOF, "exit"));
		else if (!*new_input)
		{
			free(new_input);
			continue ;
		}
		error = append_token(&new_input, tail, shell);
		if (error)
			return (error);
		error = append_input(new_input, original_input);
		if (error)
			return (error);
		free(new_input);
		return (error);
	}
}

static t_error	*append_token(char **input, t_list *tail,
		t_minishell_state *shell)
{
	t_error	*error;
	t_list	*new_token;

	new_token = NULL;
	error = check_quote(input, shell);
	if (is_error(error))
		return (error);
	error = str_to_token(*input, &new_token);
	if (is_error(error))
	{
		if (new_token)
			lstclear_token(&new_token);
		return (error);
	}
	error = check_syntax(&new_token, input, shell);
	if (is_error(error))
	{
		if (new_token)
			lstclear_token(&new_token);
		return (error);
	}
	tail->next = new_token;
	return (NULL);
}

static t_error	*append_input(char *new_input, char **original_input)
{
	char	*tmp;

	tmp = ft_strjoin(*original_input, " ");
	if (!tmp)
		return (new_error(EXIT_INTERNAL_ERR, "append_input, malloc error"));
	free(*original_input);
	*original_input = tmp;
	tmp = ft_strjoin(*original_input, new_input);
	if (!tmp)
		return (new_error(EXIT_INTERNAL_ERR, "append_input, malloc error"));
	free(*original_input);
	*original_input = tmp;
	return (NULL);
}
