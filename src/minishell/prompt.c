/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:27:14 by tkisaku           #+#    #+#             */
/*   Updated: 2025/07/01 16:14:00 by saueda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit_status.h"
#include "minishell.h"
#include "signal_handler.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static char	*get_input_str(t_minishell_state *shell);
static bool	cleanup_input_str(char *input_str, t_minishell_state *shell);

bool	prompt(t_minishell_state *shell)
{
	char	*input_str;

	input_str = get_input_str(shell);
	if (input_str == NULL)
		return (true);
	run_cmd(&input_str, shell);
	return (cleanup_input_str(input_str, shell));
}

static char	*get_input_str(t_minishell_state *shell)
{
	char	*input_str;

	(void)shell;
	while (1)
	{
		g_signal_received = 0;
		input_str = readline("minishell$ ");
		if (g_signal_received != 0)
			shell->prev_exit_code = 128 + g_signal_received;
		if (!input_str)
		{
			printf("exit\n");
			return (NULL);
		}
		if (!*input_str)
		{
			free(input_str);
			continue ;
		}
		break ;
	}
	return (input_str);
}

static bool	cleanup_input_str(char *input_str, t_minishell_state *shell)
{
	if (shell->prev_exit_code == EXIT_EOF)
	{
		free(input_str);
		return (true);
	}
	add_history(input_str);
	free(input_str);
	return (false);
}
