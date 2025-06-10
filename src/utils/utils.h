

#ifndef UTILS_H
# define UTILS_H

# include <stddef.h> //for size_t
#include <stdlib.h> //for malloc,
#include "../../libft/libft.h"
#include "ast.h"

//free_ast_1.c
void	free_ast(t_ast *ast);
void	free_command_list(t_list **command_list);
void	free_command(t_command **cmd);
void	free_redir_list(t_list **head);
//free_ast_2.c
void	free_token_list(t_list **head);
void	free_argv(char ***argv, int num);


int		ft_isspace(int c);
char	*ft_strndup(const char *s, size_t n);

#endif