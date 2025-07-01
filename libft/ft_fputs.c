/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fputs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 12:28:42 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/28 12:28:46 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include <unistd.h>

int	ft_fputs(const char *s, int fd)
{
	ssize_t	bytes;
	ssize_t	ret;

	bytes = 0;
	ret = write(fd, s, ft_strlen(s));
	if (ret == -1)
		return (-1);
	bytes += ret;
	ret = write(fd, "\n", 1);
	if (ret == -1)
		return (-1);
	bytes += ret;
	return (bytes);
}
