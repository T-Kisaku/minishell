/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 12:29:07 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/28 12:29:08 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include <stddef.h>

void	*ft_lstfind(t_list *lst, void *search_content, bool (*cmp)(void *,
			void *))
{
	while (lst)
	{
		if (cmp(search_content, lst->content))
		{
			return (lst->content);
		}
		lst = lst->next;
	}
	return (NULL);
}
