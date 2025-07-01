/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_redir_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:58 by tkisaku           #+#    #+#             */
/*   Updated: 2025/07/01 13:47:00 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "executor/redirection.h"
#include "exit_status.h"
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static void	close_opened_fd(t_redir_target *target);

/*
 *  # Behaviour
 *  - get fd with filename
 *  - dup to STDIN or STDOUT
 *  - close opened fd with filename.
 *
 *  # Warn
 *  fd of pipe is not going to be cloesd automatically
 */
int	process_redir_list(t_list *redir_list)
{
	int		exit_code;
	t_redir	*redir;

	exit_code = EXIT_OK;
	redir = NULL;
	while (redir_list)
	{
		redir = lstget_redir(redir_list);
		exit_code = process_redir(&redir->redirect_source, redir->type);
		if (exit_code != 0)
			return (exit_code);
		exit_code = process_redir(&redir->to_be_redirected, redir->type);
		if (exit_code != 0)
		{
			close_opened_fd(&redir->redirect_source);
			return (exit_code);
		}
		dup2(redir->redirect_source.fd, redir->to_be_redirected.fd);
		close_opened_fd(&redir->to_be_redirected);
		close_opened_fd(&redir->redirect_source);
		redir_list = redir_list->next;
	}
	return (exit_code);
}

static void	close_opened_fd(t_redir_target *target)
{
	if (!target->is_direct_to_fd)
		close(target->fd);
}
