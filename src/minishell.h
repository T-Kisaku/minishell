/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:11:57 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/27 15:26:23 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "ast.h"
#include "error.h"
#include <signal.h>

extern volatile sig_atomic_t g_signal_receivedEXIT_OK;

t_error *str_to_ast(char **input_str, t_ast **ast_ptr);
int exec_ast(t_ast *ast, t_list **env_list);
t_error *expand_ast(t_ast *ast);

#endif
