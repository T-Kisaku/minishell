/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:55:11 by tkisaku           #+#    #+#             */
/*   Updated: 2024/11/13 10:55:11 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// 0  : \n
// 127: DELL
int	ft_isascii(int c)
{
	if (0 <= c && c <= 127)
		return (1);
	return (0);
}
