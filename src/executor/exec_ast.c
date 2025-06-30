/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:58 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/30 12:28:35 by saueda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "executor.h"
#include "exit_status.h"
#include "minishell.h"
#include <fcntl.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>

// same meaning as exec_and_or
int	exec_ast(t_ast *ast, t_list **env_list)
{
	t_list		*andor_list;
	t_and_or	*andor;
	int			exit_code;
	bool		exec_next;

	andor_list = ast;
	exec_next = true;
	exit_code = EXIT_OK;
	while (andor_list)
	{
		andor = lstget_and_or(andor_list);
		if (exec_next)
			exit_code = exec_pipeline(andor->pipeline, env_list);
		if (andor->op_next == OP_AND)
			exec_next = exit_code == EXIT_OK;
		else if (andor->op_next == OP_OR)
			exec_next = true;
		else
			break ;
		andor_list = andor_list->next;
	}
	return (exit_code);
}
