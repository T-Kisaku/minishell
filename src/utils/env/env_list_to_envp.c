/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 11:21:01 by saueda            #+#    #+#             */
/*   Updated: 2025/06/29 11:24:51 by saueda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "exit_status.h"
#include "libft.h"
#include "utils/env.h"
#include "utils/utils.h"

static t_error	*create_env_string(char **env_str, t_env *env);

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
		error = create_env_string(&new_envp[i], env_tmp);
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

static t_error	*create_env_string(char **env_str, t_env *env)
{
	size_t	env_str_size;

	env_str_size = (ft_strlen(env->key) + ft_strlen(env->value) + 1 + 1)
		* sizeof(char);
	*env_str = malloc(env_str_size);
	if (!*env_str)
		return (new_error(EXIT_INTERNAL_ERR, "MALLOC ERROR"));
	(*env_str)[0] = '\0';
	ft_strlcat(*env_str, env->key, env_str_size);
	ft_strlcat(*env_str, "=", env_str_size);
	ft_strlcat(*env_str, env->value, env_str_size);
	return (NULL);
}
