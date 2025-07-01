/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_fd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:13:42 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/30 11:14:03 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/command.h"
#include <unistd.h>

void	dup_io(t_io_fd *io_fd)
{
	io_fd->in = dup(STDIN_FILENO);
	io_fd->out = dup(STDOUT_FILENO);
}

void	restore_close_io(t_io_fd io_fd)
{
	dup2(io_fd.in, STDIN_FILENO);
	close(io_fd.in);
	dup2(io_fd.out, STDOUT_FILENO);
	close(io_fd.out);
}
