/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:58 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 10:31:02 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "executor/command/builtin.h"
#include "exit_status.h"
#include "ft_stdio.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	print_error(const char *message)
{
	ft_fputs(message, STDERR_FILENO);
	return (EXIT_USER_ERR);
}

static int	print_internal_error(const char *message)
{
	ft_fputs(message, STDERR_FILENO);
	return (EXIT_INTERNAL_ERR);
}

int	exec_pwd(t_command *cmd, t_list **env_list)
{
	char	*cwd;

	(void)env_list;
	if (cmd->type != CMD_SIMPLE)
	{
		return (print_internal_error("pwd: invalid command type\n"));
	}
	if (cmd->u.simple.argc != 1)
	{
		return (print_error("pwd: too many arguments\n"));
	}
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		return (print_internal_error("pwd: failed to get cwd\n"));
	}
	printf("%s\n", cwd);
	free(cwd);
	return (EXIT_OK);
}
