/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:57 by tkisaku           #+#    #+#             */
/*   Updated: 2025/07/03 19:26:57 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "exit_status.h"
#include "ft_stdio.h"
#include "minishell.h"
#include "utils/env.h"
#include <stdio.h>
#include <unistd.h>

static void	print_env_etry(void *content);

int	exec_env(t_command *cmd, t_minishell_state *shell)
{
	if (cmd->type != CMD_SIMPLE)
	{
		ft_fputs("cmd->type should be CMD_SIMPLE bro", STDERR_FILENO);
		return (EXIT_INTERNAL_ERR);
	}
	if (cmd->u.simple.argc != 1)
	{
		ft_fputs("env: expected no arguments and no options", STDERR_FILENO);
		return (EXIT_USER_ERR);
	}
	ft_lstiter(shell->env_list, print_env_etry);
	return (EXIT_OK);
}

static void	print_env_etry(void *content)
{
	t_env	*env;

	env = (t_env *)content;
  if(!env || !env->key || !env->value)
    return;
	printf("%s=%s\n", env->key, env->value);
}
