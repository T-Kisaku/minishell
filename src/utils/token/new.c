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

#include "libft.h"
#include "token.h"
#include <stddef.h>

t_token	*new_token(char *value, t_token_type type)
{
	t_token	*new;

	if (!value)
		return (NULL);
	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = ft_strdup(value);
	if (!new->value)
	{
		free(new);
		return (NULL);
	}
	new->type = type;
	return (new);
}

t_list	*lstnew_token(char *value, t_token_type type)
{
	t_token	*new;
	t_list	*new_list;

	new = new_token(value, type);
	if (!new)
		return (NULL);
	new_list = ft_lstnew((void *)new);
	if (!new_list)
	{
		del_token(new);
		return (NULL);
	}
	return (new_list);
}

// Return last node of list
t_list	*lstadd_back_token(t_list **token_list_ptr, char *value,
		t_token_type type)
{
	t_list	*new_list;

	new_list = lstnew_token(value, type);
	ft_lstadd_back(token_list_ptr, new_list);
	return (new_list);
}
