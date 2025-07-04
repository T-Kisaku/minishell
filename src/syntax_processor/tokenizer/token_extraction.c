/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_extraction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:57 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 14:47:29 by saueda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "exit_status.h"
#include "syntax_processor/tokenizer.h"
#include "token.h"
#include "ft_string.h"
#include <stdio.h>

t_error	*extract_and_add_token(t_token_context *ctx, t_token_type type)
{
	char	*value;
	size_t	len;

	len = ctx->cur_str - ctx->start_str;
	value = ft_substr(ctx->start_str, 0, len);
	if (!value)
		return (new_error(EXIT_INTERNAL_ERR,
				"use strerror to make propper erro"));
	if (lstadd_back_token(ctx->head, value, type) == NULL)
	{
		free(value);
		return (new_error(EXIT_INTERNAL_ERR, "TODO: propper erro"));
	}
	free(value);
	ctx->start_str = ctx->cur_str;
	return (NULL);
}
