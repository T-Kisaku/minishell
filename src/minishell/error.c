/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:26:05 by tkisaku           #+#    #+#             */
/*   Updated: 2025/07/03 14:26:20 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "exit_status.h"
#include "ft_stdio.h"
#include "minishell.h"
#include <unistd.h>

static void	print_error(t_error *error);

void	handle_error(t_error *error, t_minishell_state *shell)
{
	if (is_error(error))
	{
		shell->prev_exit_code = error->exit_code;
		print_error(error);
		del_error(error);
	}
	else
		shell->prev_exit_code = EXIT_OK;
}

static void	print_error(t_error *error)
{
	if (error == NULL || error->msg == NULL)
		return ;
	if (error->exit_code == EXIT_EOF)
		ft_fputs(error->msg, STDOUT_FILENO);
	else
		ft_fputs(error->msg, STDERR_FILENO);
}
