/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:56 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 11:21:48 by saueda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "exit_status.h"
#include "libft.h"
#include "utils/argv.h"
#include "utils/env.h"
#include <stdlib.h>

t_env	*new_env(char *key, char *value)
{
	t_env	*new_env;

	new_env = malloc(sizeof(t_env));
	if (!new_env)
		return (NULL);
	new_env->key = ft_strdup(key);
	if (!new_env->key)
	{
		free(new_env);
		return (NULL);
	}
	new_env->value = ft_strdup(value);
	if (!new_env->value)
	{
		free(new_env->key);
		free(new_env);
		return (NULL);
	}
	return (new_env);
}

t_env	*str_to_new_env(char *env_str)
{
	t_env	*new;
	char	*key;
	char	*value;
	char	*equal_pos;

	if (!env_str)
		return (NULL);
	equal_pos = ft_strchr(env_str, '=');
	if (!equal_pos)
		return (NULL);
	key = ft_substr(env_str, 0, equal_pos - env_str);
	if (!key)
		return (NULL);
	value = equal_pos + 1;
	new = new_env(key, value);
	free(key);
	return (new);
}
// Invalid env string

t_list	*lstnew_env(char *env_str)
{
	t_env	*new;

	new = str_to_new_env(env_str);
	if (!new)
		return (NULL);
	return (ft_lstnew(new));
}

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
			ft_lstclear(env_list_ptr, del_env);
			return (new_error(EXIT_INTERNAL_ERR, "WOW"));
		}
		ft_lstadd_back(env_list_ptr, new_env_node);
		env_i++;
	}
	return (NULL);
}
