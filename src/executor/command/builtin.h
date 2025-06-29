/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 09:40:02 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 09:40:28 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "ast.h"

typedef int			(*t_builtin_func)(t_command *, t_list **env_list);

typedef struct s_builtin_entry
{
	const char		*name;
	t_builtin_func	func;
}					t_builtin_entry;

int					exec_pwd(t_command *cmd, t_list **env_list);
int					exec_env(t_command *cmd, t_list **env_list);
int					exec_export(t_command *cmd, t_list **env_list);
int					exec_unset(t_command *cmd, t_list **env_list);
int					exec_exit(t_command *cmd, t_list **env_list);
int					exec_cd(t_command *cmd, t_list **env_list);
int					exec_echo(t_command *cmd, t_list **env_list);

#endif // !BUILTIN_H
