/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:58 by tkisaku           #+#    #+#             */
/*   Updated: 2025/07/01 12:59:00 by saueda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "executor/pipeline.h"
#include "exit_status.h"
#include "minishell.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int	exec_pipeline(t_pipeline *pipeline, t_minishell_state *shell)
{
	int	exit_code;
	int	cmd_count;

	cmd_count = ft_lstsize(pipeline->command_list);
	shell->pids = get_pids(cmd_count);
	if (!shell->pids)
	{
		perror("malloc");
		return (EXIT_INTERNAL_ERR);
	}
	exit_code = exec_cmd_list(pipeline->command_list, shell);
	if (exit_code == -1)
		exit_code = wait_pids(shell->pids);
	else
		wait_pids(shell->pids);
	free(shell->pids);
	shell->pids = NULL;
	return (exit_code);
}
