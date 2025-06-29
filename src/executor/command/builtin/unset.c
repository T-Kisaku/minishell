/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:58 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 08:52:58 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "executor/command/builtin.h"
#include "exit_status.h"
#include "ft_list.h"
#include "ft_stdio.h"
#include "libft.h"
#include "utils/env.h"
#include <stdio.h>
#include <unistd.h>

static void	set_env_entry(t_list **env_list, char *env_key);
int	exec_unset(t_command *cmd, t_list **env_list)
{
	int	i;

	if (cmd->type != CMD_SIMPLE)
	{
		ft_fputs("cmd->type should be CMD_SIMPLE bro", STDERR_FILENO);
		return (EXIT_INTERNAL_ERR);
	}
	i = 1;
	while (i < cmd->u.simple.argc && cmd->u.simple.argv[i] != NULL)
	{
		set_env_entry(env_list, cmd->u.simple.argv[i]);
		i++;
	}
	return (EXIT_OK);
}

static void	set_env_entry(t_list **env_list, char *env_key)
{
	t_env	*to_be_deleted;

	to_be_deleted = new_env(env_key, "dummy");
	if (!to_be_deleted)
		return ;
	ft_lstunset(env_list, to_be_deleted, cmp_env_key, del_env);
	del_env(to_be_deleted);
}
