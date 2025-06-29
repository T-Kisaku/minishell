/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:58 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 16:30:15 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "ft_string.h"
#include "utils/argv.h"
#include "utils/env.h"
#include <stdio.h>
#include <unistd.h>

static char	*get_command_path(const char *cmd, t_list *env_list);
static char	**get_path_arr(t_list *env_list);
static char	*find_path(char **path_arr, const char *cmd_str);

char	*set_cmd_path(t_command *cmd, t_list *env_list)
{
	char	*full_path;

	full_path = get_command_path(cmd->u.simple.argv[0], env_list);
	if (!full_path)
		return (NULL);
	free(cmd->u.simple.argv[0]);
	cmd->u.simple.argv[0] = full_path;
	return (full_path);
}

static char	*get_command_path(const char *cmd_str, t_list *env_list)
{
	char	**path_arr;
	char	*full_path;

	if (!cmd_str || !*cmd_str)
		return (NULL);
	if (ft_strchr(cmd_str, '/'))
	{
		if (access(cmd_str, X_OK) == 0)
			ft_strdup(cmd_str);
		else
			return (NULL);
	}
	path_arr = get_path_arr(env_list);
	if (!path_arr)
		return (NULL);
	full_path = find_path(path_arr, cmd_str);
	free_argv_null(&path_arr);
	return (full_path);
}

static char	**get_path_arr(t_list *env_list)
{
	char	**paths;
	char	*path_env;
	t_error	*error;

	error = ms_getenv("PATH", &path_env, env_list);
	if (is_error(error))
	{
		del_error(error);
		return (NULL);
	}
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	free(path_env);
	if (!paths)
		return (NULL);
	return (paths);
}

static char	*find_path(char **path_arr, const char *cmd_str)
{
	char	*full_path;
	char	*temp;
	int		i;

	i = 0;
	while (path_arr[i])
	{
		temp = ft_strjoin(path_arr[i], "/");
		full_path = ft_strjoin(temp, cmd_str);
		free(temp);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}
