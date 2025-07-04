/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:41:55 by tkisaku           #+#    #+#             */
/*   Updated: 2025/07/04 18:08:27 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/get_next_line.h"

void	reset_t_string(t_string *str)
{
	if (str == NULL)
		return ;
	if (str->string != NULL)
	{
		free(str->string);
		str->string = NULL;
	}
	str->length = 0;
	str->capacity = 0;
}
