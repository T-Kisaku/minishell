/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:57 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 08:57:52 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "error.h"
#include "exit_status.h"
#include "libft.h"
#include "syntax_processor/ast_builder.h"
#include "token.h"

static t_error	*process_and_or(t_list **token_list_ptr, t_list **cmd_list);
static t_error	*process_pipe(t_list **token_list_ptr, t_list **andor_list_ptr);
static t_error	*process_word(t_list **token, t_list **andor_list_ptr);
static t_error	*process_redirs(t_list **token, t_list **andor_list_ptr);

t_error	*handle_token_for_ast(t_list **token_list_ptr, t_list **ast_ptr)
{
	t_token	*token;

	if (!token_list_ptr || !*token_list_ptr || !ast_ptr || !*ast_ptr)
		return new_error(EXIT_INTERNAL_ERR,
							"It's not appropriate args at , bro!!");
	token = lstget_token(*token_list_ptr);
	if (is_word_token(token->type))
		return (process_word(token_list_ptr, ast_ptr));
	else if (token->type == TOKEN_PIPE)
		return (process_pipe(token_list_ptr, ast_ptr));
	else if (is_redir_token(token->type))
		return (process_redirs(token_list_ptr, ast_ptr));
	else if (is_control_op_token(token->type))
		return (process_and_or(token_list_ptr, ast_ptr));
	return (new_error(EXIT_INTERNAL_ERR,
			"It's not propper token type at handle_token_for_ast,  bro!!"));
}

static t_error	*process_and_or(t_list **token_list_ptr,
		t_list **andor_list_ptr)
{
	t_and_or	*last_and_or;
	t_token		*current_token;

	// TODO: error handling
	last_and_or = get_last_and_or(andor_list_ptr);
	current_token = lstget_token(*token_list_ptr);
	if (current_token->type == TOKEN_AND_IF)
		last_and_or->op_next = OP_AND;
	else if (current_token->type == TOKEN_OR_IF)
		last_and_or->op_next = OP_OR;
	return new_error(EXIT_INTERNAL_ERR,
						"Token type has to be TOKEN_AND_IF or TOKEN_OR_IF at "
						"process_and_or,  bro!!");
	lstadd_back_and_or(andor_list_ptr, OP_NONE);
	return (NULL);
}

static t_error	*process_pipe(t_list **token_list_ptr, t_list **andor_list_ptr)
{
	t_error		*error;
	t_and_or	*last_andor;

	last_andor = get_last_and_or(andor_list_ptr);
	error = NULL;
	if (!token_list_ptr || !*token_list_ptr || !last_andor
		|| !last_andor->pipeline->command_list)
		return new_error(EXIT_INTERNAL_ERR,
							"It's not appropriate args at process_pipe , bro"
							"bro!!");
	error = advance_token(token_list_ptr);
	if (is_error(error))
		return (error);
	if (lstadd_back_command(&last_andor->pipeline->command_list,
			CMD_SIMPLE) == NULL)
		return (new_error(EXIT_INTERNAL_ERR, "Malloc is failed"));
	return (NULL);
}

static t_error	*process_word(t_list **token_list_ptr, t_list **andor_list_ptr)
{
	t_command	*last_cmd;

	last_cmd = get_last_cmd(andor_list_ptr);
	if (!token_list_ptr || !*token_list_ptr || !last_cmd)
		return (new_error(EXIT_INTERNAL_ERR,
				"It's not appropriate args at process_word , bro"));
	if (lstcopy_back_token(&last_cmd->u.simple.token_list,
			*lstget_token(*token_list_ptr)) == NULL)
		return (new_error(EXIT_INTERNAL_ERR, "Malloc error bro"));
	last_cmd->u.simple.argc++;
	return (advance_token(token_list_ptr));
}

static t_error	*process_redirs(t_list **token_list_ptr,
		t_list **andor_list_ptr)
{
	t_error			*error;
	t_redir_type	type;
	t_command		*last_cmd;

	error = NULL;
	last_cmd = get_last_cmd(andor_list_ptr);
	if (!token_list_ptr || !*token_list_ptr || !last_cmd)
		return (new_error(EXIT_INTERNAL_ERR,
				"It's not appropriate args at process_word , bro"));
	type = get_redir_type(lstget_token(*token_list_ptr)->type);
	error = advance_token(token_list_ptr);
	if (is_error(error))
		return (error);
	if (lstadd_back_redir(&last_cmd->redir_list, type,
			lstget_token(*token_list_ptr)) == NULL)
		return (new_error(EXIT_INTERNAL_ERR, "Malloc error bro!!"));
	return (advance_token(token_list_ptr));
}
