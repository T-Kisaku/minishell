/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:57 by tkisaku           #+#    #+#             */
/*   Updated: 2025/07/03 14:25:35 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "ft_string.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// TODO: think about when malloc is failed
t_error	*new_error(int exit_code, const char *msg)
{
	t_error	*err;

	err = malloc(sizeof(t_error));
	if (!err)
		return (NULL);
	err->exit_code = exit_code;
	if (msg == NULL)
	{
		err->msg = NULL;
		return (err);
	}
	err->msg = ft_strdup(msg);
	if (!err->msg)
	{
		free(err);
		return (NULL);
	}
	return (err);
}

bool	is_error(t_error *error)
{
	return (error != NULL);
}

void	del_error(t_error *error)
{
	if (is_error(error))
	{
		free(error->msg);
		free(error);
	}
}
