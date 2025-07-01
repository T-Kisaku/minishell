/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:57 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 15:50:27 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "exit_status.h"
#include "ft_list.h"
#include "ft_printf.h"
#include "ft_string.h"
#include "ft_stdio.h"
#include "utils/env.h"
#include "utils/path.h"
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	validate_cd_args(t_command *cmd)
{
	if (cmd->type != CMD_SIMPLE)
	{
		ft_fputs("cd: invalid command type", STDERR_FILENO);
		return (EXIT_INTERNAL_ERR);
	}
	if (cmd->u.simple.argc > 2)
	{
		ft_fputs("cd: too many arguments", STDERR_FILENO);
		return (EXIT_USER_ERR);
	}
	return (EXIT_OK);
}

char	*get_target_path(t_command *cmd, t_list *env_list, t_error **error)
{
	char	*path;

	if (cmd->u.simple.argc == 1)
	{
		*error = ms_getenv("HOME", &path, env_list);
		if (is_error(*error))
			return (NULL);
	}
	else
	{
		path = ft_strdup(cmd->u.simple.argv[1]);
		if (!path)
		{
			*error = new_error(EXIT_INTERNAL_ERR,
					"cd: memory allocation failed");
			return (NULL);
		}
	}
	return (path);
}

int	change_directory(const char *path)
{
	if (!is_cd_target_valid(path))
		return (EXIT_USER_ERR);
	if (chdir(path) != 0)
	{
		ft_dprintf(STDERR_FILENO, "cd: %s: %s\n", path, strerror(errno));
		return (EXIT_USER_ERR);
	}
	return (EXIT_OK);
}

void	update_environment_variables(t_list **env_list_ptr, const char *new_pwd)
{
	t_env	*env_var;
	char	*old_pwd;

	env_var = new_env("PWD", (char *)new_pwd);
	if (env_var)
	{
		ft_lstinsert(env_list_ptr, env_var, cmp_env_key, set_env);
		del_env(env_var);
	}
	old_pwd = getcwd(NULL, 0);
	if (old_pwd)
	{
		env_var = new_env("OLDPWD", old_pwd);
		if (env_var)
		{
			ft_lstinsert(env_list_ptr, env_var, cmp_env_key, set_env);
			del_env(env_var);
		}
		free(old_pwd);
	}
}
