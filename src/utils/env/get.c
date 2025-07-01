/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:57 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 10:46:37 by saueda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit_status.h"
#include "ft_list.h"
#include "ft_string.h"
#include "utils/env.h"
#include <stdlib.h>

t_env	*lstget_env(t_list *node)
{
	if (!node || !node->content)
		return (NULL);
	return ((t_env *)node->content);
}

bool	cmp_env_key(void *target, void *content)
{
	t_env	*casted_target;
	t_env	*casted_content;

	casted_target = NULL;
	casted_content = NULL;
	if (target == NULL || content == NULL)
		return (false);
	casted_target = (t_env *)target;
	casted_content = (t_env *)content;
	return (ft_strcmp(casted_target->key, casted_content->key) == 0);
}

t_error	*ms_getenv(char *search_key, char **value_ptr, t_list *env_list)
{
	t_env	*search_env;
	t_env	*found;
	char	*target;

	search_env = new_env(search_key, "dummy");
	if (!search_env)
		return (new_error(EXIT_INTERNAL_ERR, "MALLOC ERROR"));
	found = ft_lstfind(env_list, search_env, cmp_env_key);
	if (found == NULL)
		target = "";
	else
		target = found->value;
	*value_ptr = ft_strdup(target);
	del_env(search_env);
	if (!(*value_ptr))
	{
		return (new_error(EXIT_INTERNAL_ERR, "MALLOC ERROR"));
	}
	return (NULL);
}
