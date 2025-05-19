/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:55:12 by tkisaku           #+#    #+#             */
/*   Updated: 2024/11/13 10:55:12 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total_size;
	char	*joined;

	total_size = ft_strlen(s1) + ft_strlen(s2) + 1;
	joined = ft_calloc(total_size, sizeof(char));
	if (joined == NULL)
		return (NULL);
	ft_strlcat(joined, s1, total_size);
	ft_strlcat(joined, s2, total_size);
	return (joined);
}
