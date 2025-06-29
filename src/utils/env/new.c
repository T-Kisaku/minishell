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
		return (NULL); // Invalid env string
	key = ft_substr(env_str, 0, equal_pos - env_str);
	if (!key)
		return (NULL);
	value = equal_pos + 1;
	new = new_env(key, value);
	free(key);
	return (new);
}

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

t_error	*env_list_to_envp(t_list *env_list, char ***envp_ptr)
{
	char	**new_envp;
	size_t	new_env_str_size;
	t_env	*env_tmp;
	int		i;

	new_envp = ft_calloc(ft_lstsize(env_list) + 1, sizeof(char *));
	i = 0;
	while (env_list)
	{
		env_tmp = lstget_env(env_list);
		new_env_str_size = (ft_strlen(env_tmp->key) + ft_strlen(env_tmp->value)
				+ 1 + 1) * sizeof(char);
		new_envp[i] = malloc(new_env_str_size);
		if (!new_envp[i])
		{
			free_argv(&new_envp, i);
			return (NULL);
		}
		new_envp[i][0] = '\0';
		ft_strlcat(new_envp[i], env_tmp->key, new_env_str_size);
		ft_strlcat(new_envp[i], "=", new_env_str_size);
		ft_strlcat(new_envp[i], env_tmp->value, new_env_str_size);
		i++;
		env_list = env_list->next;
	}
	*envp_ptr = new_envp;
	return (NULL);
}
