/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:59 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 15:58:08 by saueda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "ft_string.h"
#include <stdio.h>

static t_error	*process_simple(t_list *head);
static int		count_words(char *str);
static char		*count_words_core(char *str, int *word_count);
static void		handle_quote_state(char c, bool *in_quote, char *quote_char);

t_error	*word_split_handler(t_command *cmd, t_minishell_state *shell)
{
	t_error	*error;

	(void)shell;
	error = NULL;
	if (cmd->type == CMD_SIMPLE)
	{
		error = process_simple(cmd->u.simple.token_list);
		if (is_error(error))
			return (error);
		cmd->u.simple.argc = ft_lstsize((t_list *)cmd->u.simple.token_list);
	}
	return (NULL);
}

t_error	*process_simple(t_list *head)
{
	t_list	*cur;
	t_token	*cur_token_content;
	int		word_count;
	t_error	*error;

	error = NULL;
	cur = head;
	while (cur)
	{
		cur_token_content = cur->content;
		if (cur_token_content->type == TOKEN_UNQUOTED_WORD)
		{
			word_count = count_words(cur_token_content->value);
			if (word_count > 1)
			{
				error = split_token(cur, word_count);
				if (is_error(error))
					return (error);
			}
		}
		cur = cur->next;
	}
	return (error);
}

// static int	count_words(char *str)
// {
// 	int	word_count;

// 	if (!str)
// 		return (-1);
// 	word_count = 0;
// 	while (*str)
// 	{
// 		while (ft_isspace(*str))
// 			str++;
// 		if (*str && !ft_isspace(*str))
// 		{
// 			word_count++;
// 			while (*str && !ft_isspace(*str))
// 				str++;
// 		}
// 	}
// 	return (word_count);
// }
static int	count_words(char *str)
{
	int	word_count;

	if (!str)
		return (-1);
	word_count = 0;
	while (*str)
	{
		while (ft_isspace(*str))
			str++;
		str = count_words_core(str, &word_count);
	}
	return (word_count);
}

static char	*count_words_core(char *str, int *word_count)
{
	bool	in_quote;
	char	quote;

	in_quote = false;
	if (*str && !ft_isspace(*str))
	{
		(*word_count)++;
		while (*str && (!ft_isspace(*str) || in_quote))
		{
			handle_quote_state(*str, &in_quote, &quote);
			str++;
		}
	}
	return (str);
}

static void	handle_quote_state(char c, bool *in_quote, char *quote_char)
{
	if (*in_quote)
	{
		if (c == *quote_char)
		{
			*in_quote = false;
			*quote_char = '\0';
		}
	}
	else
	{
		if (c == '\'' || c == '"')
		{
			*in_quote = true;
			*quote_char = c;
		}
	}
}
