/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del.c                                              :+:      :+:    :+:   */
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

void	del_token(void *content)
{
	t_token	*token;

	if (!content)
		return ;
	token = (t_token *)content;
	free(token->value);
	free(token);
}

void	lstclear_token(t_list **head)
{
	if (!head || !*head)
		return ;
	ft_lstclear(head, del_token);
}
