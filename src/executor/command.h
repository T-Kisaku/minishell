/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:55 by tkisaku           #+#    #+#             */
/*   Updated: 2025/07/01 10:55:47 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
#define COMMAND_H

#include "ft_list.h"
#include "ast.h"
#include "minishell.h"
#include <unistd.h>

typedef struct s_io_fd {
  int in;
  int out;
} t_io_fd;

void dup_io(t_io_fd *io_fd);
int process_redir_list(t_list *redir_list);
void restore_close_io(t_io_fd io_fd);

bool is_builtin(t_command *cmd);
pid_t exec_external_cmd(t_command *cmd, t_minishell_state *shell);
pid_t exec_builtin_cmd(t_command *cmd, int *exit_code,
                       bool is_in_pipeline, t_minishell_state *shell);

#endif // !COMMAND_H
