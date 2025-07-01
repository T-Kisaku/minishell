/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 09:40:02 by tkisaku           #+#    #+#             */
/*   Updated: 2025/07/01 10:58:39 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "ast.h"
# include "minishell.h"

typedef int			(*t_builtin_func)(t_command *, t_minishell_state *shell);

typedef struct s_builtin_entry
{
	const char		*name;
	t_builtin_func	func;
}					t_builtin_entry;

int					exec_pwd(t_command *cmd, t_minishell_state *shell);
int					exec_env(t_command *cmd, t_minishell_state *shell);
int					exec_export(t_command *cmd, t_minishell_state *shell);
int					exec_unset(t_command *cmd, t_minishell_state *shell);
int					exec_exit(t_command *cmd, t_minishell_state *shell);
int					exec_cd(t_command *cmd, t_minishell_state *shell);
int					exec_echo(t_command *cmd, t_minishell_state *shell);

#endif // !BUILTIN_H
