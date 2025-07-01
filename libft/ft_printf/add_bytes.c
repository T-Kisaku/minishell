/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_bytes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:52:31 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/28 11:55:24 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

int	add_bytes(int new_bytes, int *bytes)
{
	if (bytes == NULL)
		*bytes = 0;
	if (new_bytes == -1)
		return (-1);
	*bytes += new_bytes;
	return (*bytes);
}
