/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:41:58 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 17:26:25 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include <stdlib.h>
#include <stddef.h>

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

// #include <stdio.h>
// int main(void) {
//   printf("%p\n", calloc(0, 0));
//   printf("%p\n", ft_calloc(0, 0));
//   return (EXIT_SUCCESS);
// }
