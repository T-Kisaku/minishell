/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:59 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 08:52:59 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "exit_status.h"
#include "expander.h"
#include "ft_string.h"

static t_error	*init_split_token_context(t_split_token_context *ctx,
					t_list *token_node);
static t_error	*generate_value(t_split_token_context *ctx);
t_error			*generate_token(t_split_token_context *ctx);

t_error	*split_token(t_list *token, int word_count)
{
	t_split_token_context	ctx;
	t_token					*token_content;
	t_error					*error;

	error = NULL;
	init_split_token_context(&ctx, token);
	token_content = (t_token *)token->content;
	free(token_content->value);
	error = generate_value(&ctx);
	if (is_error(error))
	{
		free(ctx.original);
		return (error);
	}
	while (--word_count)
	{
		error = generate_value(&ctx);
		if (is_error(error))
		{
			free(ctx.original);
			return (error);
		}
	}
	free(ctx.original);
	return (error);
}

static t_error	*init_split_token_context(t_split_token_context *ctx,
		t_list *token_node)
{
	t_token	*cur_token_content;

	ctx->cur = token_node;
	ctx->next = token_node->next;
	ctx->tmp = NULL;
	cur_token_content = (t_token *)ctx->cur->content;
	ctx->original = ft_strdup(cur_token_content->value);
	if (!ctx->original)
		return (new_error(EXIT_INTERNAL_ERR, "MALLOC Error"));
	ctx->start_str = ctx->original;
	ctx->cur_str = ctx->original;
	return (0);
}

static t_error	*generate_value(t_split_token_context *ctx)
{
	t_token	*cur_token_content;

	while (*ctx->cur_str && ft_isspace(*ctx->cur_str))
		ctx->cur_str++;
	ctx->start_str = ctx->cur_str;
	while (*ctx->cur_str && !ft_isspace(*ctx->cur_str))
		ctx->cur_str++;
	cur_token_content = (t_token *)ctx->cur->content;
	cur_token_content->value = malloc(sizeof(char) * (ctx->cur_str
				- ctx->start_str + 1));
	if (!cur_token_content->value)
		return (new_error(EXIT_INTERNAL_ERR, "MALLOC ERRO"));
	ft_memcpy((char *)cur_token_content->value, (char *)ctx->start_str,
		ctx->cur_str - ctx->start_str);
	cur_token_content->value[ctx->cur_str - ctx->start_str] = '\0';
	return (NULL);
}

t_error	*generate_token(t_split_token_context *ctx)
{
	t_token	*cur_token_content;

	ctx->tmp = malloc(sizeof(t_list));
	if (!ctx->tmp)
		return (new_error(EXIT_INTERNAL_ERR, "MALLOC ERRO"));
	ctx->cur->next = ctx->tmp;
	ctx->tmp->next = ctx->next;
	ctx->cur = ctx->tmp;
	ctx->next = ctx->cur->next;
	ctx->cur->content = malloc(sizeof(t_token));
	if (!ctx->cur->content)
		return (new_error(EXIT_INTERNAL_ERR, "MALLOC ERRO"));
	cur_token_content = (t_token *)ctx->cur->content;
	cur_token_content->type = TOKEN_UNQUOTED_WORD;
	return (generate_value(ctx));
}
