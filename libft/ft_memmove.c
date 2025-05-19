/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:55:12 by tkisaku           #+#    #+#             */
/*   Updated: 2024/11/20 17:13:41 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

/**
 * The difference between memcpy and memmove is how to copy regarding overlap
 *
 * Copy backward: Overlap exists, and dest is located within the range of src
 *   src ------>
 *    ---------------
 *    | HelloWorld  |
 *    ---------------
 *       dest ------>
 *
 * Copy forward: Except above case
 *
 * Note: Copying backward ensures that data at the end of src is copied first,
 * preserving the original content during the operation.
 */

static void	copy_backward(unsigned char *dest, const unsigned char *src,
		size_t n)
{
	size_t	i;

	i = n;
	while (0 < i)
	{
		dest[i - 1] = src[i - 1];
		i--;
	}
}

static void	copy_forward(unsigned char *dest, const unsigned char *src,
		size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (s < d && d <= s + n)
		copy_backward(d, s, n);
	else
		copy_forward(d, s, n);
	return (dest);
}
