/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_processor.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:54 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 08:52:54 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_PROCESSOR_H
# define SYNTAX_PROCESSOR_H

# include "ast.h"
# include "error.h"
# include "libft.h"

t_error	*str_to_token(char *input_str, t_list **token_list_ptr);
t_error	*token_to_ast(t_list *token_list, t_ast **ast_ptr);

#endif
