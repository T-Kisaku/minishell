/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:57 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 08:52:57 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "exit_status.h"
#include "ft_string.h"
#include "syntax_processor/tokenizer.h"
#include "token.h"
#include <stdio.h>

static void		process_space(t_token_context *ctx);
static t_error	*process_unquoted_word(t_token_context *ctx);
static t_error	*process_quoted_word(t_token_context *ctx);

t_error	*tokenize_loop(t_token_context *ctx)
{
	t_error	*error;

	error = NULL;
	while (*ctx->cur_str)
	{
		process_space(ctx);
		if (*ctx->cur_str == '<' || *ctx->cur_str == '>'
			|| *ctx->cur_str == '|')
		{
			error = process_special_char(ctx);
			if (is_error(error))
				return (error);
		}
		else if (*ctx->cur_str == '\'' || *ctx->cur_str == '"')
		{
			error = process_quoted_word(ctx);
			if (is_error(error))
				return (error);
		}
		else
		{
			error = process_unquoted_word(ctx);
			if (is_error(error))
				return (error);
		}
	}
	return (error);
}

static void	process_space(t_token_context *ctx)
{
	while (ft_isspace(*ctx->cur_str))
		ctx->cur_str++;
	ctx->start_str = ctx->cur_str;
}

// unquoted string
static t_error	*process_unquoted_word(t_token_context *ctx)
{
	int		in_quote;
	char	quote;

	if (*ctx->cur_str == '\0' || ft_isspace(*ctx->cur_str)
		|| is_special_char(*ctx->cur_str))
		return (NULL);
	in_quote = 0;
	quote = '\0';
	while ((*ctx->cur_str != '\0' && !ft_isspace(*ctx->cur_str)
			&& !is_special_char(*ctx->cur_str)) || in_quote)
	{
		if (*ctx->cur_str == '\'' || *ctx->cur_str == '"')
		{
			if (in_quote && *ctx->cur_str == quote)
			{
				in_quote = 0;
				quote = '\0';
			}
			else if (!in_quote)
			{
				in_quote = 1;
				quote = *ctx->cur_str;
			}
		}
		ctx->cur_str++;
	}
	return (extract_and_add_token(ctx, TOKEN_UNQUOTED_WORD));
}

// quoted string
static t_error	*process_quoted_word(t_token_context *ctx)
{
	char			quote;
	t_token_type	type;
	t_error			*error;

	error = NULL;
	quote = *ctx->cur_str;
	if (quote != '\'' && quote != '"')
		return (new_error(EXIT_INTERNAL_ERR,
				"minishell: syntax error: invalid quote type\n"));
	if (quote == '\'')
		type = TOKEN_SINGLE_QUOTED_WORD;
	else if (quote == '"')
		type = TOKEN_DOUBLE_QUOTED_WORD;
	ctx->cur_str++;
	ctx->start_str = ctx->cur_str;
	while (*ctx->cur_str != '\0' && *ctx->cur_str != quote)
		ctx->cur_str++;
	/* if (*ctx->cur_str == '\0') { */
	/*   user_error("minishell: syntax error: unclosed quote\n"); */
	/*   return (EXIT_USER_ERR); */
	/* } */
	error = extract_and_add_token(ctx, type);
	if (is_error(error))
		return (error);
	ctx->cur_str++;
	ctx->start_str = ctx->cur_str;
	return (error);
}
