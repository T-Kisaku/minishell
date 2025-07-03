/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 11:01:27 by saueda            #+#    #+#             */
/*   Updated: 2025/07/03 11:22:45 by saueda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit_status.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

static int	set_sigquit(struct sigaction *sa);
static int	set_sigpipe(struct sigaction *sa);

int	setup_child_signals(void)
{
	struct sigaction	sa;

	if (set_sigquit(&sa) != EXIT_SUCCESS)
	{
		perror("child process: sigaction SIGQUIT");
		return (EXIT_INTERNAL_ERR);
	}
	if (set_sigpipe(&sa) != EXIT_SUCCESS)
	{
		perror("child process: sigaction SIGPIPE");
		return (EXIT_INTERNAL_ERR);
	}
	return (EXIT_SUCCESS);
}

static int	set_sigquit(struct sigaction *sa)
{
	sa->sa_handler = SIG_DFL;
	sigemptyset(&sa->sa_mask);
	sa->sa_flags = 0;
	if (sigaction(SIGQUIT, sa, NULL) == -1)
		return (EXIT_INTERNAL_ERR);
	return (EXIT_SUCCESS);
}

static int	set_sigpipe(struct sigaction *sa)
{
	sa->sa_handler = SIG_DFL;
	sigemptyset(&sa->sa_mask);
	sa->sa_flags = 0;
	if (sigaction(SIGPIPE, sa, NULL) == -1)
		return (EXIT_INTERNAL_ERR);
	return (EXIT_SUCCESS);
}
