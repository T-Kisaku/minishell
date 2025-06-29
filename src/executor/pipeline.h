/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:55 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 17:43:12 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPELINE_H
# define PIPELINE_H

# include "ft_list.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <unistd.h>


int		exec_cmd_list(pid_t *pids, t_list *cmd_list, t_list **env_list);
pid_t* get_pids(int cmd_count);
void	set_last_pid(int *pids, int pid_to_set);
int		wait_pids(pid_t *pids);

#endif // !PIPELINE_H
