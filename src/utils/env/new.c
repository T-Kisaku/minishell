/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:56 by tkisaku           #+#    #+#             */
/*   Updated: 2025/07/04 10:29:04 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "utils/env.h"
#include <stdlib.h>

static t_env	*allocate_value(t_env *new_env, char *value);

t_env	*new_env(char *key, char *value)
{
	t_env	*new_env;

	if (!key)
		return (NULL);
	new_env = malloc(sizeof(t_env));
	if (!new_env)
		return (NULL);
	new_env->key = ft_strdup(key);
	if (!new_env->key)
	{
		free(new_env);
		return (NULL);
	}
	return (allocate_value(new_env, value));
}

static t_env	*allocate_value(t_env *new_env, char *value)
{
	if (value == NULL)
	{
		new_env->value = NULL;
		return (new_env);
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
		return (new_env(env_str, NULL));
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
	t_list	*new_list;

	new = str_to_new_env(env_str);
	if (!new)
		return (NULL);
	new_list = ft_lstnew(new);
	if (!new_list)
	{
		del_env(new);
		return (NULL);
	}
	return (new_list);
}
