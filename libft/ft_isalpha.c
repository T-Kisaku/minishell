/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:52:24 by tkisaku           #+#    #+#             */
/*   Updated: 2024/11/13 16:32:32 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	is_lower(int c)
{
	return ('a' <= c && c <= 'z');
}

static int	is_upper(int c)
{
	return ('A' <= c && c <= 'Z');
}

int	ft_isalpha(int c)
{
	if (is_upper(c) || is_lower(c))
		return (1);
	return (0);
}
