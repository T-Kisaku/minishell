/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:59:33 by tkisaku           #+#    #+#             */
/*   Updated: 2025/07/01 16:09:21 by saueda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit_status.h"
#include "ft_stdio.h"
#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

static t_ast	*get_ast(char **input, t_minishell_state *shell);

void	run_cmd(char **input, t_minishell_state *shell)
{
	t_ast	*ast;

	if (!*input)
	{
		printf("\n");
		return ;
	}
	ast = get_ast(input, shell);
	shell->ast = ast;
	if (ast == NULL)
		return ;
	shell->prev_exit_code = exec_ast(ast, shell);
	printf("after exec_ast: %d\n", shell->prev_exit_code);
	lstclear_and_or(&ast);
	return ;
}

static t_ast	*get_ast(char **input, t_minishell_state *shell)
{
	t_ast	*ast;
	t_error	*error;

	ast = NULL;
	error = str_to_ast(input, &ast, shell);
	if (is_error(error))
	{
		if (error->exit_code == EXIT_EOF)
			ft_fputs(error->msg, STDOUT_FILENO);
		else
			ft_fputs(error->msg, STDERR_FILENO);
		shell->prev_exit_code = error->exit_code;
		del_error(error);
		return (NULL);
	}
	error = expand_ast(ast, shell);
	if (is_error(error))
	{
		shell->prev_exit_code = error->exit_code;
		ft_fputs(error->msg, STDERR_FILENO);
		del_error(error);
		lstclear_and_or(&ast);
		return (NULL);
	}
	return (ast);
}
