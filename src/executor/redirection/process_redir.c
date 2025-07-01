/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:37:30 by tkisaku           #+#    #+#             */
/*   Updated: 2025/07/01 13:57:00 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "exit_status.h"
#include "token.h"
#include "utils/path.h"
#include "ft_printf.h"
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static int	get_oflags(t_redir_type type);
static int	open_target(t_redir_target *target, t_redir_type type, int oflags);
static int	unlink_heredoc_tmp(t_redir_type type, char *filename);

int	process_redir(t_redir_target *target, t_redir_type type)
{
	int	oflags;

	if (target->is_direct_to_fd)
		return (EXIT_OK);
	if (validate_infile(target->filename) != 0)
		return (EXIT_USER_ERR);
	oflags = get_oflags(type);
	return (open_target(target, type, oflags));
}

static int	get_oflags(t_redir_type type)
{
	if (type == REDIR_INPUT || type == REDIR_HERE_DOC)
		return (O_RDONLY);
	if (type == REDIR_OUTPUT)
		return (O_WRONLY | O_CREAT | O_TRUNC);
	if (type == REDIR_APPEND)
		return (O_WRONLY | O_CREAT | O_APPEND);
	return (O_RDONLY);
}

static int	open_target(t_redir_target *target, t_redir_type type, int oflags)
{
	int	exit_code;

	exit_code = EXIT_OK;
	target->fd = open(target->filename, oflags, 0644);
	if (target->fd < 0)
	{
		perror("open");
		return (EXIT_INTERNAL_ERR);
	}
	target->is_direct_to_fd = true;
	del_token(target->filename_token);
	target->filename_token = NULL;
	exit_code = unlink_heredoc_tmp(type, target->filename);
	if (exit_code != EXIT_OK)
	{
		free(target->filename);
		return (exit_code);
	}
	free(target->filename);
	target->filename = NULL;
	return (exit_code);
}

static int	unlink_heredoc_tmp(t_redir_type type, char *filename)
{
	if (type != REDIR_HERE_DOC)
		return (EXIT_OK);
	if (unlink(filename) == 0)
		return (EXIT_OK);
	ft_dprintf(STDERR_FILENO, "unlink error");
	return (EXIT_INTERNAL_ERR);
}
