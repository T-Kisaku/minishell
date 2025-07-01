/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:55 by tkisaku           #+#    #+#             */
/*   Updated: 2025/07/01 08:44:47 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
#define COMMAND_H

#include "ft_list.h"
#include "ast.h"
#include <unistd.h>

typedef struct s_io_fd {
  int in;
  int out;
} t_io_fd;

void dup_io(t_io_fd *io_fd);
int process_redir_list(t_list *redir_list);
void restore_close_io(t_io_fd io_fd);

bool is_builtin(t_command *cmd);
pid_t exec_external_cmd(t_command *cmd, t_list *env_list);
pid_t exec_builtin_cmd(t_command *cmd, t_list **env_list, int *exit_code,
                       bool is_in_pipeline);

#endif // !COMMAND_H
