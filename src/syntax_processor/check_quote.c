#include "error.h"
#include "exit_status.h"
#include <stdlib.h>
#include "ft_string.h"
#include "minishell.h"
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>

static bool is_quote_closed(char *input);

t_error *check_quote(char **input, t_minishell_state *shell) {
  char *new_input;
  char *read_str;
  char *temp;
  t_error *error;

  error = NULL;
  while (1) {
    if (is_quote_closed(*input))
      return (error);
    if (shell->is_interactive != 0)
      return new_error(EXIT_USER_ERR,
                       "syntax error: You need to close quote bro!!");
    read_str = readline("> ");
    if (!read_str) {
      printf("exit\n");
      if (*input)
        free(*input);
      *input = NULL;
      rl_clear_history();
      exit(EXIT_OK);
    }
    if (!*read_str) {
      free(read_str);
      continue;
    }
    new_input = ft_strjoin(*input, "\n");
    free(*input);
    if (!new_input)
      return (new_error(EXIT_INTERNAL_ERR, "Memory allocation failed"));
    temp = new_input;
    new_input = ft_strjoin(new_input, read_str);
    free(read_str);
    free(temp);
    if (!new_input)
      return (new_error(EXIT_INTERNAL_ERR, "Memory allocation failed"));
    *input = new_input;
  }
}

static bool is_quote_closed(char *input) {
  int in_quote;
  char quote;

  in_quote = 0;
  while (*input) {
    if (in_quote) {
      if (*input == quote)
        in_quote = 0;
    } else {
      if (*input == '\'' || *input == '"') {
        in_quote = 1;
        quote = *input;
      }
    }
    input++;
  }
  if (in_quote)
    return (false);
  return true;
}
