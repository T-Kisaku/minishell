/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_loop.c                                       :+:      :+:    :+:   */
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

t_error	*redir_loop(t_ast *ast, t_error *(*handler)(t_redir *, t_list *),
		t_list *env_list)
{
	t_list	*cur_list;
	t_list	*cmd_node;
	t_list	*redir_list;
	t_error	*error;

	error = NULL;
	if (!ast || !handler)
		return (new_error(EXIT_INTERNAL_ERR, "NOT GOOD ARGS"));
	cur_list = ast;
	while (cur_list)
	{
		cmd_node = ((t_and_or *)cur_list->content)->pipeline->command_list;
		while (cmd_node)
		{
			redir_list = ((t_command *)cmd_node->content)->redir_list;
			while (redir_list)
			{
				error = handler((t_redir *)redir_list->content, env_list);
				if (is_error(error))
					return (error);
				redir_list = redir_list->next;
			}
			cmd_node = cmd_node->next;
		}
		cur_list = cur_list->next;
	}
	return (NULL);
}
