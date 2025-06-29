/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 17:05:41 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 17:11:40 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "executor/pipeline/cmd_list.h"
#include "ft_list.h"
#include <sys/wait.h>
#include <unistd.h>

static void	set_pipe_write(t_command *cmd, t_cmd_fd cmd_fd);
static void	set_prev_pipe_read(t_command *cmd, t_cmd_fd cmd_fd);

void	set_io_redir(t_command *cmd, t_cmd_fd cmd_fd)
{
	if (!cmd)
		return ;
	if (cmd_fd.current_pipe[PIPE_WRITE] >= 0)
		set_pipe_write(cmd, cmd_fd);
	if (cmd_fd.prev_pipe_read >= 0)
		set_prev_pipe_read(cmd, cmd_fd);
}

static void	set_pipe_write(t_command *cmd, t_cmd_fd cmd_fd)
{
	t_redir	*redir;

	redir = new_redir();
	if (!redir)
		return ;
	redir->type = REDIR_OUTPUT;
	redir->to_be_redirected.fd = STDOUT_FILENO;
	redir->to_be_redirected.is_direct_to_fd = true;
	redir->redirect_source.fd = cmd_fd.current_pipe[PIPE_WRITE];
	redir->redirect_source.is_direct_to_fd = true;
	ft_lstadd_front(&cmd->redir_list, ft_lstnew((void *)redir));
}

static void	set_prev_pipe_read(t_command *cmd, t_cmd_fd cmd_fd)
{
	t_redir	*redir;

	redir = new_redir();
	if (!redir)
		return ;
	redir->type = REDIR_INPUT;
	redir->to_be_redirected.fd = STDIN_FILENO;
	redir->to_be_redirected.is_direct_to_fd = true;
	redir->redirect_source.fd = cmd_fd.prev_pipe_read;
	redir->redirect_source.is_direct_to_fd = true;
	ft_lstadd_front(&cmd->redir_list, ft_lstnew((void *)redir));
}
