/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:55 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 08:52:55 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPELINE_H
#define PIPELINE_H

#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "libft.h"

int exec_cmd_list(pid_t *pids, t_list *cmd_list, t_list **env_list);
int wait_pids(pid_t *pids, int cmd_count);

#endif // !PIPELINE_H
