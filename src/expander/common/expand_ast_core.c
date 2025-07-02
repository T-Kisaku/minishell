/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_ast_core.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:58 by tkisaku           #+#    #+#             */
/*   Updated: 2025/07/02 10:23:40 by saueda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static t_error	*expand_ast_core_core_core(t_expansion_context *ctx,
					t_error *(*func)(t_expansion_context *,
						t_minishell_state *), t_minishell_state *shell,
					t_expander_mode mode);

t_error	*expand_ast_core_core(t_expansion_context *ctx,
		t_minishell_state *shell, t_expander_mode mode)
{
	t_error	*error;

	error = NULL;
	if (ctx->cur_dollar_type == DOLLAR_SPECIAL)
	{
		error = expand_ast_core_core_core(ctx, expand_special, shell, mode);
		if (is_error(error))
			return (error);
	}
	else if (ctx->cur_dollar_type == DOLLAR_VARIABLE)
	{
		error = expand_ast_core_core_core(ctx, expand_variable, shell, mode);
		if (is_error(error))
			return (error);
	}
	else if (ctx->cur_dollar_type == DOLLAR_LITERAL)
	{
		if (mode == MODE_CALCULATE)
			ctx->index++;
		else if (mode == MODE_SET_VALUE)
			copy_and_advance(ctx, --ctx->cur_pos, 1);
	}
	return (error);
}

t_error	*expand_ast_core_core_core(t_expansion_context *ctx,
		t_error *(*func)(t_expansion_context *, t_minishell_state *),
		t_minishell_state *shell, t_expander_mode mode)
{
	int		len;
	t_error	*error;

	error = func(ctx, shell);
	if (is_error(error))
	{
		free(ctx->variable);
		ctx->variable = NULL;
		return (error);
	}
	if (mode == MODE_SET_VALUE)
		*ctx->type = TOKEN_SINGLE_QUOTED_WORD;
	len = ft_strlen(ctx->variable);
	if (mode == MODE_SET_VALUE && len > 0)
		ft_memcpy(&ctx->output[ctx->index], ctx->variable, len);
	ctx->index += len;
	free(ctx->variable);
	ctx->variable = NULL;
	return (NULL);
}
