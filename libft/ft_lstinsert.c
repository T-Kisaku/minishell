/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 09:54:38 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 09:54:50 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

void	*ft_lstinsert(t_list **lst_ptr, void *ideal_content, bool (*cmp)(void *,
			void *), void (*set)(void *, void *))
{
	void	*found;

	found = ft_lstfind(*lst_ptr, ideal_content, cmp);
	if (!found)
	{
		ft_lstadd_back(lst_ptr, ft_lstnew(ideal_content));
		return (ft_lstlast(*lst_ptr));
	}
	set(found, ideal_content);
	return (found);
}
