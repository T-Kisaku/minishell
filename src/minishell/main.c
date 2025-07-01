/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:55 by tkisaku           #+#    #+#             */
/*   Updated: 2025/07/01 11:19:59 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "exit_status.h"
#include "ft_printf.h"
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

volatile sig_atomic_t	g_signal_received = 0;

static int	init_shell_state(int argc, char **argv, char **envp,
				t_minishell_state *shell);
static bool	is_option_c(int argc, char **argv);
static int	is_executable(int argc);

// TODO: this is only bash -c, adapt echo "ls" | minishell
// TODO: return exit code of bash -c
int	main(int argc, char **argv, char **envp)
{
	t_minishell_state	shell;
	int					exit_code;

	exit_code = init_shell_state(argc, argv, envp, &shell);
	if (exit_code != EXIT_OK)
		return (exit_code);
	exit_code = setup_signal_handlers();
	if (exit_code != EXIT_OK)
		return (exit_code);
	if (is_option_c(argc, argv))
	{
		run_cmd(&argv[2], &shell);
		return (EXIT_SUCCESS);
	}
	exit_code = is_executable(argc);
	if (exit_code != EXIT_OK)
		return (exit_code);
	while (1)
		if (prompt(&shell))
			break ;
	rl_clear_history();
	lstclear_env(&shell.env_list);
	return (exit_code);
}

static int	init_shell_state(int argc, char **argv, char **envp,
		t_minishell_state *shell)
{
	t_error	*error;

  shell->ast = NULL;
	shell->env_list = NULL;
  shell->pids = NULL;
	shell->prev_exit_code = 0;
	shell->is_interactive = isatty(STDIN_FILENO) == 0 || is_option_c(argc,
			argv);
	error = envp_to_env_list(envp, &shell->env_list);
	if (is_error(error))
	{
		ft_dprintf(STDERR_FILENO, "%s\n", error->msg);
		del_error(error);
		return (EXIT_INTERNAL_ERR);
	}
	return (EXIT_OK);
}

static bool	is_option_c(int argc, char **argv)
{
	return (argc == 3 && ft_strcmp(argv[1], "-c") == 0);
}

static int	is_executable(int argc)
{
	if (argc == 1 && isatty(STDIN_FILENO) == 0)
	{
		ft_fputs("minishell cannot execute when it's not tty except -c flag",
			STDERR_FILENO);
		return (EXIT_USER_ERR);
	}
	if (argc > 1)
	{
		ft_fputs("minishell accept only -c flag", STDERR_FILENO);
		return (EXIT_USER_ERR);
	}
	return (EXIT_OK);
}
