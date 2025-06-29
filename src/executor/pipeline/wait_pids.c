/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_pids.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:58 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 08:52:58 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit_status.h"
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>

int	wait_pids(pid_t *pids, int cmd_count)
{
	int	last_cmd_status;
	int	i;

	last_cmd_status = EXIT_OK;
	i = 0;
	while (i < cmd_count)
	{
		waitpid(pids[i], &last_cmd_status, 0);
		if (i == cmd_count - 1)
		{
			if (WIFEXITED(last_cmd_status))
				last_cmd_status = WEXITSTATUS(last_cmd_status);
			else
				last_cmd_status = EXIT_OK;
		}
		i++;
	}
	return (last_cmd_status);
}
