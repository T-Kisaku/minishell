/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:55 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 13:26:38 by saueda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "error.h"
#include "exit_status.h"
#include "ft_stdio.h"
#include "ft_string.h"
#include "minishell.h"
#include "signal_handler.h"
#include "utils/env.h"
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

static bool	is_option_c(int argc, char **argv);
static bool	prompt(t_minishell_state *shell);
static void	run_cmd(char **input, t_minishell_state *shell);

int	main(int argc, char **argv, char **envp)
{
	t_minishell_state	shell;
	t_error				*error;

	shell.env_list = NULL;
	shell.is_interactive = isatty(STDIN_FILENO) == 0 || is_option_c(argc, argv);
	error = envp_to_env_list(envp, &shell.env_list);
	if (is_error(error))
	{
		printf("wow!!");
		del_error(error);
		return (EXIT_INTERNAL_ERR);
	}
	if (setup_signal_handlers() != 0)
		return (EXIT_FAILURE);
	if (shell.is_interactive)
	{
		// TODO: this is only bash -c, adapt echo "ls" | minishell
		run_cmd(&argv[2], &shell);
		return (EXIT_SUCCESS);
	}
	if (argc > 1)
	{
		ft_fputs("minishell except only -c flags", STDERR_FILENO);
		return (EXIT_USER_ERR);
	}
	shell.prev_exit_code = 0;
	while (1)
		if (prompt(&shell))
			break ;
	rl_clear_history();
	lstclear_env(&shell.env_list);
	return (EXIT_SUCCESS);
}

static bool	is_option_c(int argc, char **argv)
{
	return (argc == 3 && ft_strcmp(argv[1], "-c") == 0);
}

// TODO: display new line aftter echo -n fire
// return whether it should exit
static bool	prompt(t_minishell_state *shell)
{
	char	*input_str;

	while (1)
	{
		input_str = readline("minishell$ ");
		if (!input_str)
		{
			printf("exit\n");
			return (true);
		}
		if (!*input_str)
		{
			free(input_str);
			continue ;
		}
		break ;
	}
	run_cmd(&input_str, shell);
	if (shell->prev_exit_code == EXIT_EOF)
	{
		free(input_str);
		return (true);
	}
	add_history(input_str);
	free(input_str);
	return (false);
}

static void	run_cmd(char **input, t_minishell_state *shell)
{
	t_ast	*ast;
	t_error	*error;

	error = NULL;
	ast = NULL;
	if (!*input)
	{
		printf("\n");
		return ;
	}
	//   (void)prev_exit_code; // TODO: pass this to expand_ast!!
	error = str_to_ast(input, &ast, shell);
	if (is_error(error))
	{
		if (error->exit_code == EXIT_EOF)
			ft_fputs(error->msg, STDOUT_FILENO);
		else
			ft_fputs(error->msg, STDERR_FILENO);
		shell->prev_exit_code = error->exit_code;
		del_error(error);
		return ;
	}
	error = expand_ast(ast, shell);
	if (is_error(error))
	{
		shell->prev_exit_code = error->exit_code;
		ft_fputs(error->msg, STDERR_FILENO);
		del_error(error);
		free_ast(&ast);
		return ;
	}
	shell->prev_exit_code = exec_ast(ast, &shell->env_list);
	free_ast(&ast);
	return ;
}
