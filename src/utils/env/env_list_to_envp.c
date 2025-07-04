/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_to_envp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 11:21:01 by saueda            #+#    #+#             */
/*   Updated: 2025/07/04 10:29:23 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "exit_status.h"
#include "ft_stdlib.h"
#include "utils/env.h"
#include "utils/utils.h"

static t_error	*create_env_string(t_env *env, char **env_str);

t_error	*env_list_to_envp(t_list *env_list, char ***envp_ptr)
{
	char	**new_envp;
	t_env	*env_tmp;
	t_error	*error;
	int		i;

	new_envp = ft_calloc(ft_lstsize(env_list) + 1, sizeof(char *));
	if (!new_envp)
		return (new_error(EXIT_INTERNAL_ERR, "MALLOC ERROR"));
	i = 0;
	while (env_list)
	{
		env_tmp = lstget_env(env_list);
		error = create_env_string(env_tmp, &new_envp[i]);
		if (error)
		{
			free_argv(&new_envp, i);
			return (error);
		}
		i++;
		env_list = env_list->next;
	}
	*envp_ptr = new_envp;
	return (NULL);
}

static t_error	*create_env_string(t_env *env, char **env_str)
{
	size_t	env_str_size;

	if (!env || !env->key)
		return (new_error(EXIT_INTERNAL_ERR, "INVALID ENV"));
	env_str_size = ft_strlen(env->key) + 2;
	if (env->value != NULL)
		env_str_size += ft_strlen(env->value) + 1;
	env_str_size *= sizeof(char);
	*env_str = malloc(env_str_size);
	if (!*env_str)
		return (new_error(EXIT_INTERNAL_ERR, "MALLOC ERROR"));
	(*env_str)[0] = '\0';
	ft_strlcat(*env_str, env->key, env_str_size);
	if (env->value != NULL)
	{
		ft_strlcat(*env_str, "=", env_str_size);
		ft_strlcat(*env_str, env->value, env_str_size);
	}
	return (NULL);
}
