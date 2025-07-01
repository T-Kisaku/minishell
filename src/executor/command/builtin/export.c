/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:58 by tkisaku           #+#    #+#             */
/*   Updated: 2025/07/01 11:01:30 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "executor/command/builtin.h"
#include "exit_status.h"
#include "ft_list.h"
#include "ft_stdio.h"
#include "ft_string.h"
#include "minishell.h"
#include "utils/env.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static void	set_env_entry(t_list **env_list, char *env_str);
static void	print_export_entry(void *content);

int	exec_export(t_command *cmd, t_minishell_state *shell)
{
	int	i;

	if (cmd->type != CMD_SIMPLE)
	{
		ft_fputs("cmd->type should be CMD_SIMPLE bro", STDERR_FILENO);
		return (EXIT_INTERNAL_ERR);
	}
	if (cmd->u.simple.argc == 1)
	{
		ft_lstiter(shell->env_list, print_export_entry);
		return (EXIT_OK);
	}
	i = 1;
	while (i < cmd->u.simple.argc && cmd->u.simple.argv[i] != NULL)
	{
		set_env_entry(&shell->env_list, cmd->u.simple.argv[i]);
		i++;
	}
	return (EXIT_OK);
}

static void	print_export_entry(void *content)
{
	t_env	*env;

	env = (t_env *)content;
	printf("declare -x %s=\"%s\"\n", env->key, env->value);
}

static void	set_env_entry(t_list **env_list, char *env_str)
{
	t_env	*found;
	t_env	*ideal_env;

	ideal_env = str_to_new_env(env_str);
	if (!ideal_env)
		return ;
	found = ft_lstfind(*env_list, ideal_env, cmp_env_key);
	if (!found)
	{
		ft_lstadd_back(env_list, ft_lstnew(ideal_env));
		return ;
	}
	free(found->value);
	found->value = ft_strdup(ideal_env->value);
	del_env(ideal_env);
}
