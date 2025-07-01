/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pointer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 22:57:12 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/28 12:34:42 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf_internal.h"

int	put_pointer(int fd, void *ptr)
{
	unsigned long	address;
	int				bytes;

	bytes = 0;
	address = (unsigned long)ptr;
	if (!ptr)
		return (write(STDOUT_FILENO, "(nil)", 5));
	if (add_bytes(put_string(fd, "0x"), &bytes) == -1)
		return (-1);
	if (add_bytes(put_hex(fd, address, false), &bytes) == -1)
		return (-1);
	return (bytes);
}
