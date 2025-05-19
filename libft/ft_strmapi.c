/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:55:12 by tkisaku           #+#    #+#             */
/*   Updated: 2024/11/13 10:55:12 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*accumulated;
	size_t	s_i;
	size_t	s_len;

	s_len = ft_strlen(s);
	accumulated = malloc((s_len + 1) * sizeof(char));
	if (accumulated == NULL)
		return (NULL);
	s_i = 0;
	while (s[s_i])
	{
		accumulated[s_i] = f(s_i, s[s_i]);
		s_i++;
	}
	accumulated[s_i] = '\0';
	return (accumulated);
}
