/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:55 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 16:03:46 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "token.h"
#include "utils/argv.h"
#include <limits.h>
#include <stdlib.h>

void	del_command(void *content)
{
	t_command	*cmd;

	if (!content)
		return ;
	cmd = (t_command *)content;
	clear_redir_list(&cmd->redir_list);
	if (cmd->type == CMD_SIMPLE)
	{
		lstclear_token(&cmd->u.simple.token_list);
		free_argv(&cmd->u.simple.argv, INT_MAX);
	}
	else if (cmd->type == CMD_SUBSHELL)
		lstclear_and_or
(&cmd->u.subshell.and_or_list);
	free(cmd);
}

void	lstclear_cmd(t_list **command_list)
{
	if (!command_list || !*command_list)
		return ;
	ft_lstclear(command_list, del_command);
}
