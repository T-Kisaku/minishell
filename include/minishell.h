/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:11:57 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/06 11:58:10 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "ast.h"

typedef struct data {
  char **lexered;
  t_ast *parsered;
} t_data;

char **lexer(char **argv);
t_ast *parse_tokens(char *tokens[]);
int exec_ast(t_ast *ast);

void cleanup(t_data data);
void error();

#endif
