/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 16:57:00 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 17:11:36 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/pipeline/cmd_list.h"
#include "ft_list.h"
#include "ft_printf.h"
#include <sys/wait.h>
#include <unistd.h>

int	init_cmd_fd(t_cmd_fd *cmd_fd)
{
	if (!cmd_fd)
	{
		return (-1);
	}
	cmd_fd->prev_pipe_read = INVALID_FD;
	cmd_fd->current_pipe[PIPE_READ] = INVALID_FD;
	cmd_fd->current_pipe[PIPE_WRITE] = INVALID_FD;
	return (0);
}

int	create_pipe_if_needed(t_cmd_fd *cmd_fd, t_list *cmd_list)
{
	if (!ft_lst_is_last(cmd_list))
	{
		if (pipe(cmd_fd->current_pipe) < 0)
		{
			ft_dprintf(STDERR_FILENO, "strerr: pipe!!");
			return (-1);
		}
	}
	return (0);
}

void	cleanup_pipe_fds(t_cmd_fd *cmd_fd)
{
	close_and_init_fd(&cmd_fd->prev_pipe_read);
	close_and_init_fd(&cmd_fd->current_pipe[PIPE_WRITE]);
	cmd_fd->prev_pipe_read = cmd_fd->current_pipe[PIPE_READ];
	cmd_fd->current_pipe[PIPE_READ] = INVALID_FD;
}

void	close_and_init_fd(int *fd)
{
	if (fd && *fd >= 0)
	{
		close(*fd);
		*fd = INVALID_FD;
	}
}
