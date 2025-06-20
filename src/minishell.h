/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:11:57 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/16 14:52:07 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "ast.h"

int str_to_ast(char *input_str, t_ast **ast_ptr);
int exec_ast(t_ast *ast);
int process_expansion(t_ast *ast);

void error();

#endif
