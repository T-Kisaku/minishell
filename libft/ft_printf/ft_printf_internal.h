/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_internal.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 22:56:55 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/28 12:20:33 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_INTERNAL_H

# define FT_PRINTF_INTERNAL_H

# include <stdarg.h>
# include <stdbool.h>
# include <stddef.h>
# include <unistd.h>

# define HEX_DIGITS "0123456789abcdef"

int	put_char(int fd, int c);
int	put_string(int fd, char *s);
int	put_int(int fd, int num);
int	put_unsigned_int(int fd, unsigned int n);
int	put_hex(int fd, unsigned long n, int is_print_upper);
int	put_pointer(int fd, void *ptr);

int	add_bytes(int new_bytes, int *bytes);

#endif // !FT_PRINTF_INTERNAL_H
