/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:55 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 08:52:55 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGV_H
# define ARGV_H

void	free_argv(char ***argv, int num);
void	free_argv_null(char ***argv);
char	**copy_argv(char **argv);
void	str_arr_iter(char **arr, void (*f)(char **, int));

void	set_env(t_list *env_list, const char *key, const char *value);
char	**remove_str(char **str_arr, const char *key);
#endif // !ARGV_H
