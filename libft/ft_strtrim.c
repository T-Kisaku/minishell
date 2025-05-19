/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:55:12 by tkisaku           #+#    #+#             */
/*   Updated: 2024/11/17 16:56:45 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define INCLUDED 1
#define NOT_INCLUDED 0

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimed;
	int		start_i;
	int		end_i;
	int		len;

	start_i = 0;
	while (s1[start_i] && ft_strchr(set, s1[start_i]))
		start_i++;
	end_i = ft_strlen(s1);
	while (start_i < end_i && ft_strchr(set, s1[end_i - 1]))
		end_i--;
	len = end_i - start_i + 1;
	trimed = ft_calloc(len, sizeof(char));
	if (trimed == NULL)
		return (NULL);
	ft_strlcpy(trimed, &s1[start_i], len);
	return (trimed);
}
