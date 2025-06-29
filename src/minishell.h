/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:11:57 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 17:52:55 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ast.h"
# include "error.h"
# include <signal.h>

typedef struct s_minishell_state
{
	t_list						*env_list;
	int							prev_exit_code;
	bool						is_interactive;
}								t_minishell_state;

extern volatile sig_atomic_t	g_signal_received;

t_error							*str_to_ast(char **input_str, t_ast **ast_ptr,
									t_minishell_state *shell);
int								exec_ast(t_ast *ast, t_list **env_list);
t_error							*expand_ast(t_ast *ast,
									t_minishell_state *shell);

bool							prompt(t_minishell_state *shell);
void							run_cmd(char **input, t_minishell_state *shell);

#endif
