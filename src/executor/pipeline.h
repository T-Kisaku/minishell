/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:55 by tkisaku           #+#    #+#             */
/*   Updated: 2025/07/01 13:02:30 by saueda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPELINE_H
# define PIPELINE_H

# include "ft_list.h"
# include "minishell.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <unistd.h>

int		exec_cmd_list(t_list *cmd_list, t_minishell_state *shell);
pid_t	*get_pids(int cmd_count);
void	set_last_pid(int *pids, int pid_to_set);
int		wait_pids(pid_t *pids);

#endif // !PIPELINE_H
