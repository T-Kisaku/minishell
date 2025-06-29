/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 16:57:13 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 17:03:05 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_LIST_H
#define CMD_LIST_H

#include "ft_list.h"
#include "ast.h"
#include <sys/wait.h>

# define PIPE_READ 0
# define PIPE_WRITE 1
# define INVALID_FD -1
# define BUILTIN_NOT_LAST -1

typedef struct s_cmd_fd
{
	int	prev_pipe_read;
	int	current_pipe[2];
}		t_cmd_fd;


void	set_io_redir(t_command *cmd, t_cmd_fd cmd_fd);
void	close_and_init_fd(int *fd);
int	init_cmd_fd(t_cmd_fd *cmd_fd);
int	create_pipe_if_needed(t_cmd_fd *cmd_fd, t_list *cmd_list);
void	cleanup_pipe_fds(t_cmd_fd *cmd_fd);

#endif // !CMD_LIST_H
