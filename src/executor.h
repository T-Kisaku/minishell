/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:54 by tkisaku           #+#    #+#             */
/*   Updated: 2025/07/01 13:05:56 by saueda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "ast.h"
# include "minishell.h"
# include <fcntl.h>
# include <stdbool.h>

int		exec_pipeline(t_pipeline *pipeline, t_minishell_state *shell);
char	*set_cmd_path(t_command *cmd, t_list *env_list);

#endif // !EXECUTOR_H
