/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 10:15:45 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 15:49:43 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "error.h"
#include "executor/command/builtin.h"
#include "executor/command/builtin/cd.h"
#include "exit_status.h"
#include "ft_list.h"
#include "ft_stdio.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int	print_free_error(t_error *error)
{
	int	ret;

	ret = error->exit_code;
	ft_fputs(error->msg, STDERR_FILENO);
	del_error(error);
	return (ret);
}

static int	clean_target_path(char *target_path, int result)
{
	free(target_path);
	return (result);
}

int	exec_cd(t_command *cmd, t_list **env_list_ptr)
{
	char	*target_path;
	char	*new_pwd;
	t_error	*error;
	int		result;

	error = NULL;
	result = validate_cd_args(cmd);
	if (result != EXIT_OK)
		return (result);
	target_path = get_target_path(cmd, *env_list_ptr, &error);
	if (error)
		return (print_free_error(error));
	if (!target_path)
		return (EXIT_OK);
	result = change_directory(target_path);
	if (result != EXIT_OK)
		return (clean_target_path(target_path, result));
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return (clean_target_path(target_path, EXIT_INTERNAL_ERR));
	update_environment_variables(env_list_ptr, new_pwd);
	free(target_path);
	free(new_pwd);
	return (EXIT_OK);
}
