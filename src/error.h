/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:54 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 17:46:48 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <stdbool.h>

typedef struct s_error
{
	int		exit_code;
	char	*msg;
}			t_error;

t_error		*new_error(int exit_code, const char *msg);
void		del_error(t_error *error);
bool		is_error(t_error *error);

#endif // !ERROR_H
