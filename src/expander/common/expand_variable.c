/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:58 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 08:52:58 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "exit_status.h"
#include "expander.h"
#include "ft_string.h"
#include "minishell.h"
#include "stdio.h"
#include "utils/env.h"

t_error			*expand_variable(t_expansion_context *ctx,
					t_minishell_state *shell);
t_error			*expand_special(t_expansion_context *ctx,
					t_minishell_state *shell);
static t_error	*set_temp(t_expansion_context *ctx, char *str,
					e_mode_set_temp mode);
static t_error	*set_prev_exit_code(t_expansion_context *ctx,
					int prev_exit_code);

t_error	*expand_variable(t_expansion_context *ctx, t_minishell_state *shell)
{
	char	*start;
	char	*tmp;
	t_error	*error;

	start = ctx->cur_pos;
	if (*ctx->cur_pos == '_' || ft_isalpha(*ctx->cur_pos))
		ctx->cur_pos++;
	else
		return (new_error(EXIT_INTERNAL_ERR, "$[_a-zA-Z]"));
	while (*ctx->cur_pos == '_' || ft_isalnum(*ctx->cur_pos))
		ctx->cur_pos++;
	tmp = ft_strndup(start, ctx->cur_pos - start);
	if (!tmp)
		return (new_error(EXIT_INTERNAL_ERR, "MALLOC ERRO"));
	error = ms_getenv(tmp, &ctx->variable, shell->env_list);
	free(tmp);
	if (error)
		return (error);
	if (!ctx->variable)
	{
		ctx->variable = malloc(sizeof(char));
		if (!ctx->variable)
			return (new_error(EXIT_INTERNAL_ERR, "MALLOC ERRO"));
		*ctx->variable = '\0';
	}
	else
	{
		ctx->variable = ft_strdup(ctx->variable);
		if (!ctx->variable)
			return (new_error(EXIT_INTERNAL_ERR, "MALLOC ERRO"));
	}
	return (NULL);
}

t_error	*expand_special(t_expansion_context *ctx, t_minishell_state *shell)
{
	(void)shell;              // shellは未使用
	if (*ctx->cur_pos == '?') // 後で実装
		return (set_prev_exit_code(ctx, shell->prev_exit_code));
	else if (*ctx->cur_pos == '$') // 後で実装
		return (set_temp(ctx, "", SET_MODE_NORMAL));
	else if (*ctx->cur_pos == '!')
		return (set_temp(ctx, "", SET_MODE_NORMAL));
	else if (*ctx->cur_pos == '0')
		return (set_temp(ctx, "minishell", SET_MODE_NORMAL));
	else if (ft_isdigit(*ctx->cur_pos))
		return (set_temp(ctx, "", SET_MODE_FIGURE));
	else if (*ctx->cur_pos == '#')
		return (set_temp(ctx, "0", SET_MODE_NORMAL));
	else if (*ctx->cur_pos == '*')
		return (set_temp(ctx, "", SET_MODE_NORMAL));
	else if (*ctx->cur_pos == '@')
		return (set_temp(ctx, "", SET_MODE_NORMAL));
	else if (*ctx->cur_pos == '_' && *ctx->next_pos != '_'
		&& !ft_isalnum(*ctx->next_pos))
		return (set_temp(ctx, "", SET_MODE_NORMAL));
	else if (*ctx->cur_pos == '-')
		return (set_temp(ctx, "", SET_MODE_NORMAL));
	return (new_error(EXIT_INTERNAL_ERR, "I don't know why bro"));
}

static t_error	*set_temp(t_expansion_context *ctx, char *str,
		e_mode_set_temp mode)
{
	if (mode == SET_MODE_FIGURE)
		while (ft_isdigit((int)*ctx->cur_pos))
			ctx->cur_pos++;
	if (!str)
	{
		return (new_error(EXIT_INTERNAL_ERR, "str is not good bro"));
	}
	ctx->variable = ft_strdup(str);
	if (!ctx->variable)
		return (new_error(EXIT_INTERNAL_ERR, "MALLOC ERRO"));
	if (mode == SET_MODE_NORMAL)
		ctx->cur_pos++;
	return (NULL);
}

static t_error	*set_prev_exit_code(t_expansion_context *ctx,
		int prev_exit_code)
{
	char	*str_exit_code;
	size_t	len;

	str_exit_code = ft_itoa(prev_exit_code);
	if (!str_exit_code)
		return (new_error(EXIT_INTERNAL_ERR, "ft_itoa error"));
	ctx->variable = str_exit_code;
	len = ft_strlen(str_exit_code);
	while (len--)
		ctx->cur_pos++;
	return (NULL);
}
