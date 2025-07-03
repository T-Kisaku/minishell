/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:41:55 by tkisaku           #+#    #+#             */
/*   Updated: 2025/07/03 14:18:06 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/get_next_line.h"

void	*ft_bzero(void *s, size_t n)
{
	unsigned char	*p;
	size_t			i;

	p = s;
	i = 0;
	while (i < n)
	{
		p[i] = 0;
		i++;
	}
	return (p);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	total_size;

	total_size = nmemb * size;
	if (size != 0 && (total_size / size != nmemb))
		return (NULL);
	ptr = malloc(total_size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, total_size);
	return (ptr);
}

/*
 * 1. Must be finished with Null-terminating.
 * 2. Must return total length of string they tried to create
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	src_len;
	unsigned int	i;

	src_len = 0;
	if (src == NULL || size == 0)
		return (src_len);
	while (src[src_len] != '\0')
		src_len++;
	i = 0;
	while (src[i] != '\0' && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}

void	reset_t_string(t_string *str)
{
	if (str == NULL)
		return ;
	if (str->string != NULL)
	{
		free(str->string);
		str->string = NULL;
	}
	str->length = 0;
	str->capacity = 0;
}
