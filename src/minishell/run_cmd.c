/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:59:33 by tkisaku           #+#    #+#             */
/*   Updated: 2025/07/03 14:25:24 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "exit_status.h"
#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

static t_error	*set_ast(char **input, t_ast **ast_ptr,
					t_minishell_state *shell);

t_error	*run_cmd(char **input, t_minishell_state *shell)
{
	t_error	*error;
	int		exit_code;

	if (!*input)
	{
		printf("\n");
		return (NULL);
	}
	shell->ast = NULL;
	error = set_ast(input, &shell->ast, shell);
	if (is_error(error))
		return (error);
	exit_code = exec_ast(shell->ast, shell);
	if (exit_code != EXIT_OK)
		error = new_error(exit_code, NULL);
	lstclear_and_or(&shell->ast);
	return (error);
}

static t_error	*set_ast(char **input, t_ast **ast_ptr,
		t_minishell_state *shell)
{
	t_error	*error;

	error = NULL;
	error = str_to_ast(input, ast_ptr, shell);
	if (is_error(error))
		return (error);
	error = expand_ast(*ast_ptr, shell);
	if (is_error(error))
	{
		lstclear_and_or(ast_ptr);
		return (error);
	}
	return (error);
}
