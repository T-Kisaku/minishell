/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:55 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 10:45:02 by saueda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "libft.h"
#include <stddef.h>

void	del_and_or(void *content)
{
	t_and_or	*and_or;

	if (!content)
		return ;
	and_or = (t_and_or *)content;
	del_pipeline(and_or->pipeline);
	free(and_or);
}

void	lstclear_and_or(t_list **and_or_list)
{
	if (!and_or_list || !*and_or_list)
		return ;
	ft_lstclear(and_or_list, del_and_or);
	*and_or_list = NULL;
}
