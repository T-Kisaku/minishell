#include <stdlib.h> //free
#include "libft.h"  //ft_lstclear
#include "ast.h"
#include "token.h"
#include "utils.h"

void free_redir_list(t_list **head);
void del_redir(void *content);
void free_token_list(t_list **head);
void del_token_content(void *content);
void free_argv(char ***argv, int num);

void free_redir_list(t_list **head) {
  if (!head || !*head)
    return;
  ft_lstclear(head, del_redir);
}

void free_token_list(t_list **head) {
  if (!head || !*head)
    return;
  ft_lstclear(head, del_token_content);
}

void del_token_content(void *content) {
  t_token_content *token_content;

  if (!content)
    return;
  token_content = (t_token_content *)content;
  free(token_content->value);
  free(token_content);
}

void free_argv(char ***argv, int num) {
  int i;

  if (!argv || !*argv)
    return;
  i = 0;
  if (num == INT_MAX)
    while ((*argv)[i]) {
      free((*argv)[i]);
      (*argv)[i] = NULL;
      i++;
    }
  else {
    while (i < num) {
      free((*argv)[i]);
      (*argv)[i] = NULL;
      i++;
    }
  }
  free(*argv);
  *argv = NULL;
}
