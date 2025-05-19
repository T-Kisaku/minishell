/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:55:12 by tkisaku           #+#    #+#             */
/*   Updated: 2024/11/13 10:55:12 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*get_empty(void)
{
	return (ft_strdup(""));
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	start_len;

	if (ft_strlen(s) <= start)
		return (get_empty());
	start_len = ft_strlen(&s[start]);
	if (start_len < len)
		len = start_len;
	if (len <= 0)
		return (get_empty());
	substr = malloc(len + 1);
	if (substr == NULL)
		return (NULL);
	ft_strlcpy(substr, &s[start], len + 1);
	return (substr);
}
