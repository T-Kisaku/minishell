/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:55 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 14:46:45 by saueda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGV_H
# define ARGV_H

void	free_argv(char ***argv, int num);
void	free_argv_null(char ***argv);
// char	**copy_argv(char **argv);
void	str_arr_iter(char **arr, void (*f)(char **, int));

char	**remove_str(char **str_arr, const char *key);
#endif // !ARGV_H
