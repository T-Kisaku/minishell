/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 10:05:32 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 10:15:33 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CD_H
# define CD_H

# include "ast.h"
# include "error.h"

int		validate_cd_args(t_command *cmd);
char	*get_target_path(t_command *cmd, t_list *env_list, t_error **error);

int		change_directory(const char *path);
void	update_environment_variables(t_list **env_list_ptr,
			const char *new_pwd);

#endif // !CD_H
