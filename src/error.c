/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:57 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 16:07:29 by tkisaku          ###   ########.fr       */
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
	err->msg = ft_strdup(msg);
	if (!err->msg)
	{
		free(err);
		return (NULL);
	}
	return (err);
}

void	del_error(t_error *error)
{
	if (error != NULL)
	{
		free(error->msg);
		free(error);
	}
}

bool	is_error(t_error *error)
{
	return (error != NULL);
}
