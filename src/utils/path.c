/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:57 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/30 13:26:08 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

// TODO: refactor path related funcs, is_cd_target_valid, get_command_path at
// executor
int	is_cd_target_valid(const char *path)
{
	struct stat	st;

	if (access(path, F_OK) != 0)
	{
		ft_dprintf(STDERR_FILENO, "cd: %s: No such file or directory\n", path);
		return (0);
	}
	if (stat(path, &st) != 0)
	{
		ft_dprintf(STDERR_FILENO, "cd: %s: %s\n", path, strerror(errno));
		return (0);
	}
	if (!S_ISDIR(st.st_mode))
	{
		ft_dprintf(STDERR_FILENO, "cd: %s: Not a directory\n", path);
		return (0);
	}
	if (access(path, X_OK) != 0)
	{
		ft_dprintf(STDERR_FILENO, "cd: %s: Permission denied\n", path);
		return (0);
	}
	return (1);
}

int	validate_infile(const char *infile)
{
	if (access(infile, F_OK) != 0)
	{
		ft_dprintf(STDERR_FILENO, "Error: file '%s' does not exist.\n", infile);
		return (-1);
	}
	if (access(infile, R_OK) != 0)
	{
		ft_dprintf(STDERR_FILENO, "Error: file '%s' is not readable.\n",
			infile);
		return (-1);
	}
	return (0);
}
