/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_argv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:59 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 10:47:20 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "exit_status.h"
#include "expander.h"
#include "minishell.h"
#include "utils/argv.h"

static t_error	*process_simple(t_command *cmd);

t_error	*generate_argv_handler(t_command *cmd, t_minishell_state *shell)
{
	t_error	*error;

	(void)shell;
	error = NULL;
	if (cmd->type == CMD_SIMPLE)
	{
		error = process_simple(cmd);
		if (is_error(error))
			return (error);
	}
	else if (cmd->type == CMD_SUBSHELL)
    return NULL;
	if (cmd->u.simple.argv == NULL)
		return (new_error(EXIT_INTERNAL_ERR, "MALLOC ERRO"));
	else
		return (error);
}

static t_error	*process_simple(t_command *cmd)
{
	t_list	*cur_token;
	t_token	*cur_token_content;
	int		index;

	cmd->u.simple.argv = malloc(sizeof(char *) * (cmd->u.simple.argc + 1));
	if (!cmd->u.simple.argv)
		return (new_error(EXIT_INTERNAL_ERR, "MALLOC ERRO"));
	cur_token = cmd->u.simple.token_list;
	index = 0;
	while (index < cmd->u.simple.argc)
	{
		cur_token_content = cur_token->content;
		cmd->u.simple.argv[index] = ft_strdup(cur_token_content->value);
		if (!cmd->u.simple.argv[index])
		{
			free_argv(&cmd->u.simple.argv, index);
			return (new_error(EXIT_INTERNAL_ERR, "MALLOC ERRO"));
		}
		index++;
		cur_token = cur_token->next;
	}
	cmd->u.simple.argv[index] = NULL;
	return (NULL);
}
