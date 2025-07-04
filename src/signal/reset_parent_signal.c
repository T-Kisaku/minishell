/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_parent_signal.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:59 by tkisaku           #+#    #+#             */
/*   Updated: 2025/07/04 15:03:06 by saueda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit_status.h"
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include "signal_handler.h"

int	reset_parent_sigint(void)
{
	struct sigaction	sa;

	if (set_sigint(&sa) != EXIT_SUCCESS)
	{
		perror("parent process: sigaction SIGINT");
		return (EXIT_INTERNAL_ERR);
	}
	return (EXIT_SUCCESS);
}
