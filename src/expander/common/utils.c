/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:58 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 08:52:58 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "libft.h"

void	copy_and_advance(t_expansion_context *ctx, char *src, int count);

void	copy_and_advance(t_expansion_context *ctx, char *src, int count)
{
	int	i;

	ft_memcpy(&ctx->output[ctx->index], src, count);
	i = 0;
	while (i < count)
	{
		ctx->cur_pos++;
		ctx->index++;
		i++;
	}
}
