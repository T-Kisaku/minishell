/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:57 by tkisaku           #+#    #+#             */
/*   Updated: 2025/07/04 17:42:57 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "executor/command.h"
#include "executor/command/builtin.h"
#include "exit_status.h"
#include "ft_stdio.h"
#include "ft_string.h"
#include "minishell.h"
#include <stdbool.h>
#include <unistd.h>

static const t_builtin_entry	*find_builtin(const char *name);
static const t_builtin_entry	*get_builtin_table(void);

int	exec_builtin_cmd(t_command *cmd, t_minishell_state *shell)
{
	const t_builtin_entry	*entry;

	if (!is_builtin(cmd))
		return (-1);
	entry = find_builtin(cmd->u.simple.argv[0]);
	if (!entry || !entry->func)
	{
		ft_fputs("entry data for builtin is broken", STDERR_FILENO);
		return (EXIT_INTERNAL_ERR);
	}
	return (entry->func(cmd, shell));
}

bool	is_builtin(t_command *cmd)
{
	if (cmd->type != CMD_SIMPLE)
		return (false);
	return (find_builtin(cmd->u.simple.argv[0]) != NULL);
}

static const t_builtin_entry	*find_builtin(const char *name)
{
	const t_builtin_entry	*table;
	int						i;

	table = get_builtin_table();
	i = 0;
	while (table[i].name != NULL)
	{
		if (ft_strcmp(table[i].name, name) == 0)
			return (&table[i]);
		i++;
	}
	return (NULL);
}

static const t_builtin_entry	*get_builtin_table(void)
{
	static const t_builtin_entry	table[8] = {
	{"echo", exec_echo},
	{"exit", exec_exit},
	{"env", exec_env},
	{"export", exec_export},
	{"unset", exec_unset},
	{"pwd", exec_pwd},
	{"cd", exec_cd},
	{NULL, NULL}
	};

	return (table);
}
