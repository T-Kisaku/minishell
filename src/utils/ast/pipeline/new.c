/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:56 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 08:52:56 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include <stddef.h>
#include <stdlib.h>

t_pipeline	*new_pipeline(void)
{
	t_pipeline	*new;

	new = malloc(sizeof(t_pipeline));
	if (!new)
		return (NULL);
	new->command_list = NULL;
	return (new);
}
