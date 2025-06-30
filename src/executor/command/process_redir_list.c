/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_redir_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:58 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/30 12:31:03 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "exit_status.h"
#include "token.h"
#include "utils/path.h"
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static int	process(t_redir_target *target, t_redir_type type);
static void	close_opened_fd(t_redir_target *target);

// TODO: handle error for dup, open, close or any other funcitons related to fd
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
		exit_code = process(&redir->redirect_source, redir->type);
		if (exit_code != 0)
			return (exit_code);
		exit_code = process(&redir->to_be_redirected, redir->type);
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

static int	process(t_redir_target *target, t_redir_type type)
{
	int	oflags;

	if (!target->is_direct_to_fd)
	{
		if (type == REDIR_INPUT || REDIR_HERE_DOC)
		{
			if (validate_infile(target->filename) != 0)
				return (EXIT_USER_ERR);
			oflags = O_RDONLY;
		}
		if (type == REDIR_OUTPUT)
			oflags = O_WRONLY | O_CREAT | O_TRUNC;
		if (type == REDIR_APPEND)
			oflags = O_WRONLY | O_CREAT | O_APPEND;
		target->fd = open(target->filename, oflags, 0644);
		if (target->fd < 0)
		{
			perror("open");
			return (EXIT_INTERNAL_ERR);
		}
		target->is_direct_to_fd = true;
		del_token(target->filename_token);
		target->filename_token = NULL;
		if (type == REDIR_HERE_DOC)
		{
			if (unlink(target->filename) == -1)
			{
				dprintf(STDERR_FILENO, "unlink error");
				free(target->filename);
				target->filename = NULL;
				return (EXIT_INTERNAL_ERR);
			}
		}
		free(target->filename);
		target->filename = NULL;
	}
	return (EXIT_OK);
}

static void	close_opened_fd(t_redir_target *target)
{
	if (!target->is_direct_to_fd)
		close(target->fd);
}
