/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:11:57 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/12 16:02:15 by saueda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "ast.h"

t_ast* argv_to_ast(char** argv);
int exec_ast(t_ast *ast);

void cleanup(t_data data);
void error();

#endif
