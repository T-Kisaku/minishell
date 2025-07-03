/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pids.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:58 by tkisaku           #+#    #+#             */
/*   Updated: 2025/07/04 08:05:56 by saueda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit_status.h"
#include "ft_string.h"
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "signal_handler.h"

pid_t	*get_pids(int cmd_count)
{
	pid_t	*pids;
	size_t	total_size;

	total_size = (cmd_count + 1) * sizeof(pid_t);
	pids = malloc(total_size);
	if (pids == NULL)
		return (NULL);
	ft_memset((void *)pids, -1, total_size);
	return (pids);
}

void	set_last_pid(int *pids, int pid_to_set)
{
	int	i;

	i = 0;
	while (pids[i] != -1)
		i++;
	pids[i] = pid_to_set;
}

int	wait_pids(pid_t *pids)
{
	int	last_cmd_status;
	int	i;

	last_cmd_status = EXIT_OK;
	i = 0;
	while (pids[i] != -1)
	{
		waitpid(pids[i], &last_cmd_status, 0);
		i++;
	}
	print_child_signal_message(last_cmd_status);
	if (WIFEXITED(last_cmd_status))
		last_cmd_status = WEXITSTATUS(last_cmd_status);
	else
		last_cmd_status = EXIT_OK;
	return (last_cmd_status);
}
