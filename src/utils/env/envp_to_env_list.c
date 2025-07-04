/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_to_env_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:01:26 by tkisaku           #+#    #+#             */
/*   Updated: 2025/07/04 17:01:26 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "exit_status.h"
#include "utils/env.h"
#include <stdlib.h>

t_error	*envp_to_env_list(char **envp, t_list **env_list_ptr)
{
	t_list	*new_env_node;
	size_t	env_i;

	env_i = 0;
	while (envp[env_i])
	{
		new_env_node = lstnew_env(envp[env_i]);
		if (!new_env_node)
		{
			lstclear_env(env_list_ptr);
			return (new_error(EXIT_INTERNAL_ERR, "MALLOC ERROR"));
		}
		ft_lstadd_back(env_list_ptr, new_env_node);
		env_i++;
	}
	return (NULL);
}
