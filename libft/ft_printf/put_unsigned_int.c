/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_unsigned_int.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 22:57:19 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/28 12:34:08 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

int	put_unsigned_int(int fd, unsigned int n)
{
	int	bytes;

	bytes = 0;
	if (n >= 10)
		if (add_bytes(put_unsigned_int(fd, n / 10), &bytes) == -1)
			return (-1);
	if (add_bytes(put_char(fd, '0' + (n % 10)), &bytes) == -1)
		return (-1);
	return (bytes);
}
