/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 12:30:18 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/28 12:30:20 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include <stdlib.h>

char	*ft_strndup(const char *s, size_t n)
{
	char	*res;

	res = malloc(n + 1);
	if (!res)
		return (NULL);
	ft_memcpy(res, s, n);
	res[n] = '\0';
	return (res);
}
