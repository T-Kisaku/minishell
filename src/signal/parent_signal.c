/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:59 by tkisaku           #+#    #+#             */
/*   Updated: 2025/07/03 14:30:40 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit_status.h"
#include <minishell.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static void	handle_sigint(int sig);
static int	set_sigint(struct sigaction *sa);
static int	set_sigpipe(struct sigaction *sa);
static int	set_sigquit(struct sigaction *sa);

int	setup_parent_signals(void)
{
	struct sigaction	sa;

	if (set_sigint(&sa) != EXIT_SUCCESS)
	{
		perror("parent process: sigaction SIGINT");
		return (EXIT_INTERNAL_ERR);
	}
	if (set_sigquit(&sa) != EXIT_SUCCESS)
	{
		perror("parent process: sigaction SIGQUIT");
		return (EXIT_INTERNAL_ERR);
	}
	if (set_sigpipe(&sa) != EXIT_SUCCESS)
	{
		perror("parent process: sigaction SIGPIPE");
		return (EXIT_INTERNAL_ERR);
	}
	return (EXIT_SUCCESS);
}

// SIGINT(Ctrl + c)
static void	handle_sigint(int sig)
{
	(void)sig;
	g_signal_received = SIGINT;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static int	set_sigint(struct sigaction *sa)
{
	sa->sa_handler = handle_sigint;
	sigemptyset(&sa->sa_mask);
	sa->sa_flags = 0;
	if (sigaction(SIGINT, sa, NULL) == -1)
		return (EXIT_INTERNAL_ERR);
	return (EXIT_SUCCESS);
}

static int	set_sigquit(struct sigaction *sa)
{
	sa->sa_handler = SIG_IGN;
	sigemptyset(&sa->sa_mask);
	sa->sa_flags = 0;
	if (sigaction(SIGQUIT, sa, NULL) == -1)
		return (EXIT_INTERNAL_ERR);
	return (EXIT_SUCCESS);
}

static int	set_sigpipe(struct sigaction *sa)
{
	sa->sa_handler = SIG_IGN;
	sigemptyset(&sa->sa_mask);
	sa->sa_flags = 0;
	if (sigaction(SIGPIPE, sa, NULL) == -1)
		return (EXIT_INTERNAL_ERR);
	return (EXIT_SUCCESS);
}
