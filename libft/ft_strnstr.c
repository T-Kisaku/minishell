/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:55:12 by tkisaku           #+#    #+#             */
/*   Updated: 2024/11/13 10:55:12 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	big_i;
	size_t	little_len;

	if (*little == '\0')
		return ((char *)big);
	big_i = 0;
	little_len = ft_strlen(little);
	while (big[big_i] && big_i + little_len <= len)
	{
		if (ft_strncmp(&big[big_i], little, little_len) == 0)
			return ((char *)&big[big_i]);
		big_i++;
	}
	return (NULL);
}
