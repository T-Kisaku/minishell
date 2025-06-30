/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_ast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:57 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 14:24:19 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "error.h"
#include "exit_status.h"
#include "syntax_processor/ast_builder.h"
#include <stdbool.h> //bool,

static t_error	*build_ast_from_token_list(t_list **token_list,
					t_ast **ast_ptr);

t_error	*token_to_ast(t_list *token_list, t_ast **ast_ptr)
{
	t_error	*error;

	error = NULL;
	if (!token_list)
		return (new_error(EXIT_INTERNAL_ERR,
				"INTERNAL ERROR: I don't know why token_list is empty bro"));
	*ast_ptr = lstnew_and_or(OP_NONE);
	if (!*ast_ptr)
		return (new_error(EXIT_INTERNAL_ERR,
				"INTERNAL ERROR: malloc for andor is failed bro"));
	error = build_ast_from_token_list(&token_list, ast_ptr);
	if (is_error(error))
	{
		lstclear_and_or
(ast_ptr);
		return (error);
	}
	return (error);
}

static t_error	*build_ast_from_token_list(t_list **token_list_ptr,
		t_ast **ast_ptr)
{
	t_error	*error;

	error = NULL;
	while (*token_list_ptr != NULL)
	{
		error = handle_token_for_ast(token_list_ptr, ast_ptr);
		if (is_error(error))
			return (error);
	}
	return (error);
}
