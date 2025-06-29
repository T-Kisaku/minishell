/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:55 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 08:52:55 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_BUILDER_H
# define AST_BUILDER_H

# include "ast.h"
# include "error.h"
# include <stdbool.h>

t_error		*handle_token_for_ast(t_list **token_list_ptr, t_list **ast_ptr);

t_error		*advance_token(t_list **token);
t_and_or	*get_last_and_or(t_list **and_or_list_ptr);
t_command	*get_last_cmd(t_list **and_or_list_ptr);

#endif
