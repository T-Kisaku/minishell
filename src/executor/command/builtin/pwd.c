/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:58 by tkisaku           #+#    #+#             */
/*   Updated: 2025/07/01 12:59:20 by saueda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "executor/command/builtin.h"
#include "exit_status.h"
#include "ft_stdio.h"
#include "minishell.h"
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

int	exec_pwd(t_command *cmd, t_minishell_state *shell)
{
	char	*cwd;

	(void)shell;
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
