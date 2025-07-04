/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:55 by tkisaku           #+#    #+#             */
/*   Updated: 2025/07/04 17:50:29 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
#include <unistd.h>

volatile sig_atomic_t	g_signal_received = 0;

static void				prompt_loop(t_minishell_state *shell);
static bool				is_option_c(int argc, char **argv);

int	main(int argc, char **argv, char **envp)
{
	t_minishell_state	shell;

	init_shell_state(&shell);
	shell.is_interactive = isatty(STDIN_FILENO) != 0 && !is_option_c(argc,
			argv);
	handle_error(envp_to_env_list(envp, &shell.env_list), &shell);
	if (shell.prev_exit_code != EXIT_OK)
		return (shell.prev_exit_code);
	shell.prev_exit_code = setup_parent_signals();
	if (shell.prev_exit_code != EXIT_OK)
		return (shell.prev_exit_code);
	if (is_option_c(argc, argv))
	{
		handle_error(run_cmd(&argv[2], &shell), &shell);
		return (shell.prev_exit_code);
	}
	if (argc > 1)
	{
		ft_fputs("minishell accept only -c flag", STDERR_FILENO);
		return (EXIT_USER_ERR);
	}
	prompt_loop(&shell);
	rl_clear_history();
	del_shell_state(&shell);
	exit(shell.prev_exit_code);
}

static void	prompt_loop(t_minishell_state *shell)
{
	while (1)
	{
		handle_error(prompt(shell), shell);
		if (!shell->is_interactive)
			break ;
		if (shell->prev_exit_code == EXIT_EOF)
		{
			shell->prev_exit_code = EXIT_OK;
			break ;
		}
	}
}

static bool	is_option_c(int argc, char **argv)
{
	return (argc == 3 && ft_strcmp(argv[1], "-c") == 0);
}
