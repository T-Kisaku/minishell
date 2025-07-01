/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 22:57:00 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/28 12:34:52 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"
#include <stdio.h>
#include <unistd.h>

static int	ft_vdprintf(int fd, const char *format, va_list args);
static int	put_conversion(int fd, char conversion, va_list args);

int	ft_dprintf(int fd, const char *format, ...)
{
	va_list	args;
	int		result;

	va_start(args, format);
	result = ft_vdprintf(fd, format, args);
	va_end(args);
	return (result);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		result;

	va_start(args, format);
	result = ft_vdprintf(STDOUT_FILENO, format, args);
	va_end(args);
	return (result);
}

static int	ft_vdprintf(int fd, const char *format, va_list args)
{
	char	*cal_str;
	int		bytes;

	if (format == NULL)
		return (-1);
	cal_str = (char *)format;
	bytes = 0;
	while (*cal_str)
	{
		if (*cal_str == '%')
		{
			cal_str++;
			if (add_bytes(put_conversion(fd, *cal_str, args), &bytes) == -1)
				break ;
		}
		else if (add_bytes(put_char(fd, *cal_str), &bytes) == -1)
			break ;
		if (*cal_str)
			cal_str++;
	}
	return (bytes);
}

static int	put_conversion(int fd, char conversion, va_list args)
{
	if (conversion == 'c')
		return (put_char(fd, va_arg(args, int)));
	else if (conversion == 's')
		return (put_string(fd, va_arg(args, char *)));
	else if (conversion == 'p')
		return (put_pointer(fd, va_arg(args, void *)));
	else if (conversion == 'd' || conversion == 'i')
		return (put_int(fd, va_arg(args, int)));
	else if (conversion == 'u')
		return (put_unsigned_int(fd, va_arg(args, unsigned int)));
	else if (conversion == 'x')
		return (put_hex(fd, va_arg(args, unsigned int), false));
	else if (conversion == 'X')
		return (put_hex(fd, va_arg(args, unsigned int), true));
	else if (conversion == '%')
		return (put_char(fd, '%'));
	return (-1);
}
