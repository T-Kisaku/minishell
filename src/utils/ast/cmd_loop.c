/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:56 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 08:52:56 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "error.h"
#include "exit_status.h"
#include "minishell.h"

t_error	*cmd_loop(t_ast *ast, t_error *(*handler)(t_command *,
			t_minishell_state *), t_minishell_state *shell)
{
	t_list		*cur_list;
	t_and_or	*cur_and_or;
	t_list		*cmd_node;
	t_command	*cmd;
	t_error		*error;

	error = NULL;
	if (!ast || !handler)
		return (new_error(EXIT_INTERNAL_ERR, "NOT GOOD ARGS"));
	cur_list = ast;
	while (cur_list)
	{
		cur_and_or = (t_and_or *)(cur_list->content);
		cmd_node = cur_and_or->pipeline->command_list;
		while (cmd_node)
		{
			cmd = (t_command *)(cmd_node->content);
			error = handler(cmd, shell);
			if (is_error(error))
				return (error);
			cmd_node = cmd_node->next;
		}
		cur_list = cur_list->next;
	}
	return (error);
}
