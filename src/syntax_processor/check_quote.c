/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:57 by tkisaku           #+#    #+#             */
/*   Updated: 2025/07/03 11:53:37 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "exit_status.h"
#include "ft_string.h"
#include "minishell.h"
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>

static bool		is_quote_closed(char *input);
static t_error	*read_and_append_line(char **input);
static t_error	*read_line_from_readline(char **read_str);
static t_error	*append_line_to_input(char **input, const char *read_str);

// check if quote is closed and require addtional input if needed
t_error	*check_quote(char **input, t_minishell_state *shell)
{
	t_error	*error;

	if (!input || !*input || !shell)
		return (new_error(EXIT_INTERNAL_ERR,
				"Invalid arguments to check_quote"));
	while (1)
	{
		if (is_quote_closed(*input))
			return (NULL);
		if (!shell->is_interactive)
			return (new_error(EXIT_USER_ERR,
					"syntax error: You need to close quote bro!!"));
		error = read_and_append_line(input);
		if (error)
			return (error);
	}
}

static t_error	*read_and_append_line(char **input)
{
	char	*read_str;
	t_error	*error;

	error = read_line_from_readline(&read_str);
	if (error)
		return (error);
	if (!read_str)
		return (NULL);
	error = append_line_to_input(input, read_str);
	free(read_str);
	return (error);
}

static t_error	*read_line_from_readline(char **read_str)
{
	*read_str = readline("> ");
	if (!*read_str)
		return (new_error(EXIT_EOF, "exit"));
	return (NULL);
}

static t_error	*append_line_to_input(char **input, const char *read_str)
{
	char	*new_input;
	char	*temp;

	new_input = ft_strjoin(*input, "\n");
	if (!new_input)
		return (new_error(EXIT_INTERNAL_ERR, "Memory allocation failed"));
	free(*input);
	temp = new_input;
	new_input = ft_strjoin(temp, read_str);
	free(temp);
	if (!new_input)
		return (new_error(EXIT_INTERNAL_ERR, "Memory allocation failed"));
	*input = new_input;
	return (NULL);
}

static bool	is_quote_closed(char *input)
{
	bool	in_quote;
	char	quote;

	if (!input)
		return (true);
	in_quote = false;
	while (*input)
	{
		if (in_quote)
		{
			if (*input == quote)
				in_quote = false;
		}
		else
		{
			if (*input == '\'' || *input == '"')
			{
				in_quote = true;
				quote = *input;
			}
		}
		input++;
	}
	return (!in_quote);
}
