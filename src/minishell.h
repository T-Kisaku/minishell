/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:11:57 by tkisaku           #+#    #+#             */
/*   Updated: 2025/07/03 14:27:35 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ast.h"
# include "error.h"
# include <signal.h>

typedef struct s_minishell_state
{
	t_ast						*ast;
	t_list						*env_list;
	pid_t						*pids;
	int							prev_exit_code;
	bool						is_interactive;
}								t_minishell_state;

void							init_shell_state(t_minishell_state *shell);
void							del_shell_state(t_minishell_state *shell);

extern volatile sig_atomic_t	g_signal_received;

t_error							*str_to_ast(char **input_str, t_ast **ast_ptr,
									t_minishell_state *shell);
int								exec_ast(t_ast *ast, t_minishell_state *shell);
t_error							*expand_ast(t_ast *ast,
									t_minishell_state *shell);

t_error							*prompt(t_minishell_state *shell);
t_error							*run_cmd(char **input,
									t_minishell_state *shell);

void							handle_error(t_error *error,
									t_minishell_state *shell);

#endif
