/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_string.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 22:57:15 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/28 12:33:54 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_string.h"

int	put_string(int fd, char *s)
{
	int	len;

	if (s == NULL)
		return (write(fd, "(null)", 6));
	len = ft_strlen(s);
	return (write(fd, s, len));
}
