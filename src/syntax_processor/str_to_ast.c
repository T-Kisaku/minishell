/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_to_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:57 by tkisaku           #+#    #+#             */
/*   Updated: 2025/07/03 17:15:56 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "check_quote.h"
#include "error.h"
#include "minishell.h"
#include "syntax_processor.h"
#include "token.h"
#include <stdio.h>

t_error	*str_to_ast(char **input_str, t_ast **ast_ptr, t_minishell_state *shell)
{
	t_error	*error;
	t_list	*token_list;

	error = NULL;
	token_list = NULL;
	error = check_quote(input_str, shell);
	if (is_error(error))
		return (error);
	error = str_to_token(*input_str, &token_list);
	if (is_error(error))
		return (error);
	if (token_list == NULL)
		return (error);
	error = check_syntax(&token_list, input_str, shell);
	if (error)
	{
		lstclear_token(&token_list);
		return (error);
	}
	error = token_to_ast(token_list, ast_ptr);
	lstclear_token(&token_list);
	if (is_error(error))
		return (error);
	return (error);
}
