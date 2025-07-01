/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:57 by tkisaku           #+#    #+#             */
/*   Updated: 2025/07/01 12:59:48 by saueda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "exit_status.h"
#include "ft_ctype.h"
#include "ft_stdio.h"
#include "ft_stdlib.h"
#include "ft_string.h"
#include "minishell.h"

void	*check_is_all_digit(unsigned int i, char c, void *acc)
{
	bool	*is_valid;

	(void)i;
	is_valid = (bool *)acc;
	if (is_valid == false)
		return (false);
	*is_valid = ft_isdigit(c);
	return (acc);
}

bool	check_valid_ascii(char *s)
{
	bool	is_valid;

	is_valid = true;
	if (*s == '-' || *s == '+')
		s++;
	ft_strreduce(s, &is_valid, check_is_all_digit);
	return (is_valid);
}

int	exec_exit(t_command *cmd, t_minishell_state *shell)
{
	int	exit_code;

	exit_code = EXIT_OK;
	if (cmd->type != CMD_SIMPLE)
	{
		ft_fputs("cmd->type should be CMD_SIMPLE bro", STDERR_FILENO);
		exit_code = EXIT_INTERNAL_ERR;
	}
	else if (cmd->u.simple.argc == 1)
		exit_code = EXIT_OK;
	else if (cmd->u.simple.argc > 2)
	{
		ft_fputs("exit: expected less than 1 argument", STDERR_FILENO);
		exit_code = EXIT_USER_ERR;
	}
	else if (!check_valid_ascii(cmd->u.simple.argv[1]))
	{
		ft_fputs("exit: expected only 1 + or - and numeric argument",
			STDERR_FILENO);
		exit_code = EXIT_USER_ERR;
	}
	if (cmd->u.simple.argc != 1)
		exit_code = ft_atoi(cmd->u.simple.argv[1]);
	del_shell_state(shell);
	exit(exit_code);
}
