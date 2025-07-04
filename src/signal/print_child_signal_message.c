/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_child_signal_message.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:21:03 by tkisaku           #+#    #+#             */
/*   Updated: 2025/07/04 16:39:42 by saueda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "minishell.h"
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

void	print_child_signal_message(int status)
{
	if (g_signal_received != 0)
	{
		if (g_signal_received == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
		if (g_signal_received == SIGQUIT)
		{
			if (WCOREDUMP(status))
				ft_dprintf(STDERR_FILENO, "Quit (core dumped)\n");
			else
				ft_dprintf(STDERR_FILENO, "Quit\n");
		}
	}
}
