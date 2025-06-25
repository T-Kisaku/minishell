/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:11:57 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/25 09:05:31 by saueda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "ast.h"
#include "error.h"
#include <signal.h>

extern  volatile sig_atomic_t g_signal_received;

t_error *str_to_ast(char **input_str, t_ast **ast_ptr);
int exec_ast(t_ast *ast, char **envp);
t_error *expand_ast(t_ast *ast);

#endif
