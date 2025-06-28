/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstunset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 12:29:15 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/28 12:29:16 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include <stddef.h>

void	ft_lstunset(t_list **lst, void *search_content, bool (*cmp)(void *,
			void *), void (*del)(void *))
{
	t_list	*curr;
	t_list	*prev;

	curr = *lst;
	prev = NULL;
	while (curr)
	{
		if (cmp(search_content, curr->content))
		{
			if (prev)
				prev->next = curr->next;
			else
				*lst = curr->next;
			ft_lstdelone(curr, del);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}
