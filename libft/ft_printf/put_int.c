/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_int.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 22:57:09 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/28 12:22:01 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_string.h"
#include "ft_stdlib.h"

int	put_int(int fd, int num)
{
	char	*num_str;
	int		len;
	int		bytes;

	num_str = ft_itoa(num);
	len = ft_strlen(num_str);
	if (num_str)
		bytes = write(fd, num_str, len);
	else
		return (-1);
	free(num_str);
	return (bytes);
}
