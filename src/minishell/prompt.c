/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:27:14 by tkisaku           #+#    #+#             */
/*   Updated: 2025/07/03 15:17:33 by saueda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signal_handler.h"
#include "utils/get_next_line.h"
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "exit_status.h"

static char	*get_input_str(t_minishell_state *shell);

t_error	*prompt(t_minishell_state *shell)
{
	t_error	*error;
	char	*input_str;

	error = NULL;
	input_str = get_input_str(shell);
	if (input_str == NULL)
		return (new_error(EXIT_EOF, NULL));
	error = run_cmd(&input_str, shell);
	add_history(input_str);
	free(input_str);
	return (error);
}

static char	*get_input_str(t_minishell_state *shell)
{
	char	*input_str;

	while (1)
	{
		g_signal_received = 0;
		if (shell->is_interactive)
			input_str = readline("minishell$ ");
		else
			input_str = get_next_line(STDIN_FILENO);
		if (g_signal_received != 0)
			shell->prev_exit_code = 128 + g_signal_received;
		if (!input_str)
		{
			if (shell->is_interactive)
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
