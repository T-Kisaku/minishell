/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_hex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 22:57:06 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/28 12:33:43 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"
#include "ft_ctype.h"

int	put_hex(int fd, unsigned long n, int is_print_upper)
{
	char	buffer[sizeof(unsigned long) * 2 + 1];
	int		bytes;
	int		i;

	i = 0;
	bytes = 0;
	if (n == 0)
		buffer[i++] = '0';
	else
	{
		while (n > 0)
		{
			buffer[i++] = HEX_DIGITS[n % 16];
			n /= 16;
		}
	}
	buffer[i] = '\0';
	while (--i >= 0)
	{
		if (is_print_upper)
			buffer[i] = ft_toupper(buffer[i]);
		if (add_bytes(put_char(fd, buffer[i]), &bytes) == -1)
			return (-1);
	}
	return (bytes);
}
