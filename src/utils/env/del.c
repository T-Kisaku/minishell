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

#include "utils/env.h"

void	del_env(void *content)
{
	t_env	*env;

	if (!content)
		return ;
	env = (t_env *)content;
	free(env->key);
	free(env->value);
	free(env);
}

void	lstclear_env(t_list **head)
{
	if (!head || !*head)
		return ;
	ft_lstclear(head, del_env);
}
