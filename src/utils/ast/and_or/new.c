/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:55 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 08:52:55 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "libft.h"
#include <stddef.h>
#include <stdlib.h>

t_and_or	*new_and_or(t_andor_op andor_op)
{
	t_and_or	*new;

	new = malloc(sizeof(t_and_or));
	if (!new)
		return (NULL);
	new->op_next = andor_op;
	new->pipeline = new_pipeline();
	if (new->pipeline == NULL)
	{
		free(new);
		return (NULL);
	}
	return (new);
}

t_list	*lstnew_and_or(t_andor_op andor_op)
{
	t_and_or	*new;
	t_list		*new_list;

	new = new_and_or(andor_op);
	if (!new)
		return (NULL);
	new_list = ft_lstnew((void *)new);
	if (!new_list)
		free(new);
	return (new_list);
}

t_list	*lstadd_back_and_or(t_list **and_or_list_ptr, t_andor_op andor_op)
{
	t_list	*new_and_or_list;

	new_and_or_list = lstnew_and_or(andor_op);
	ft_lstadd_back(and_or_list_ptr, new_and_or_list);
	return (new_and_or_list);
}
