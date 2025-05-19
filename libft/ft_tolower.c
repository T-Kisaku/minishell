/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:55:12 by tkisaku           #+#    #+#             */
/*   Updated: 2024/11/13 16:24:25 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Refer from is_alpha
static int	is_upper(int c)
{
	return ('A' <= c && c <= 'Z');
}

int	ft_tolower(int c)
{
	if (is_upper(c))
		c += GAP_OF_CHAR;
	return (c);
}
