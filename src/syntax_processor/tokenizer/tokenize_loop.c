/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:57 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 13:59:18 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "exit_status.h"
#include "syntax_processor/tokenizer.h"
#include "token.h"
#include "ft_ctype.h"
#include <stdio.h>

static void		skip_space(t_token_context *ctx);
static t_error	*process_unquoted_word(t_token_context *ctx);
static void		set_in_quote(int *in_quote_ptr, char *quote_ptr, char cur_char);
static t_error	*process_quoted_word(t_token_context *ctx);

t_error	*tokenize_loop(t_token_context *ctx)
{
	t_error	*error;

	error = NULL;
	while (*ctx->cur_str)
	{
		skip_space(ctx);
		if (is_special_char(*ctx->cur_str))
			error = process_special_char(ctx);
		else if (is_quote_char(*ctx->cur_str))
			error = process_quoted_word(ctx);
		else
			error = process_unquoted_word(ctx);
	}
	return (error);
}

static void	skip_space(t_token_context *ctx)
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
		if (is_quote_char(*ctx->cur_str))
			set_in_quote(&in_quote, &quote, *ctx->cur_str);
		ctx->cur_str++;
	}
	return (extract_and_add_token(ctx, TOKEN_UNQUOTED_WORD));
}

static void	set_in_quote(int *in_quote_ptr, char *quote_ptr, char cur_char)
{
	if (*in_quote_ptr && cur_char == *quote_ptr)
	{
		*in_quote_ptr = 0;
		*quote_ptr = '\0';
	}
	else if (!*in_quote_ptr)
	{
		*in_quote_ptr = 1;
		*quote_ptr = cur_char;
	}
}

// quoted string
static t_error	*process_quoted_word(t_token_context *ctx)
{
	char			quote;
	t_token_type	type;
	t_error			*error;

	error = NULL;
	quote = *ctx->cur_str;
	if (!is_quote_char(quote))
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
	error = extract_and_add_token(ctx, type);
	if (is_error(error))
		return (error);
	ctx->cur_str++;
	ctx->start_str = ctx->cur_str;
	return (error);
}
