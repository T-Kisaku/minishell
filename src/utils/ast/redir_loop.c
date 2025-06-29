/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:56 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 11:42:15 by saueda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "error.h"
#include "exit_status.h"
#include "utils/utils.h"

t_error	*redir_loop(t_ast *ast, t_error *(*handler)(t_redir *,
					t_minishell_state *), t_minishell_state *shell)
{
	t_redir_loop_context	ctx;

	if (!ast || !handler)
		return (new_error(EXIT_INTERNAL_ERR, "NOT GOOD ARGS"));
	ctx.cur_list = ast;
	while (ctx.cur_list)
	{
		ctx.cmd_node
			= ((t_and_or *)ctx.cur_list->content)->pipeline->command_list;
		while (ctx.cmd_node)
		{
			ctx.redir_list = ((t_command *)ctx.cmd_node->content)->redir_list;
			while (ctx.redir_list)
			{
				ctx.error = handler((t_redir *)ctx.redir_list->content,
						shell);
				if (is_error(ctx.error))
					return (ctx.error);
				ctx.redir_list = ctx.redir_list->next;
			}
			ctx.cmd_node = ctx.cmd_node->next;
		}
		ctx.cur_list = ctx.cur_list->next;
	}
	return (NULL);
}
