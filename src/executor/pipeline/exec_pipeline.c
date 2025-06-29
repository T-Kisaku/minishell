/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:58 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 08:52:58 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "error.h"
#include "executor/pipeline.h"
#include "exit_status.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int	exec_pipeline(t_pipeline *pipeline, t_list **env_list)
{
	int		exit_code;
	pid_t	*pids;
	int		cmd_count;

	cmd_count = ft_lstsize(pipeline->command_list);
	pids = ft_calloc(cmd_count + 1, sizeof(pid_t));
	if (!pids)
	{
		perror(ERR_MSG_MALLOC);
		return (EXIT_INTERNAL_ERR);
	}
	exit_code = exec_cmd_list(pids, pipeline->command_list, env_list);
	if (exit_code == -1)
		exit_code = wait_pids(pids, cmd_count);
	else
		wait_pids(pids, cmd_count);
	free(pids);
	return (exit_code);
}
