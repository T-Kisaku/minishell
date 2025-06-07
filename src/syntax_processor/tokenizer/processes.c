#include "../../include/tokenizer.h"

int create_token(t_token_context *tc);
int set_token(t_token_context *tc, e_token_type type);
void process_space(t_token_context *tc);
int process_quoted_word(t_token_context *tc);
int process_unquoted_word(t_token_context *tc);

int create_token(t_token_context *tc) {
  t_token *new_token;

  new_token = malloc(sizeof(t_token));
  if (!new_token)
    return (write_error("malloc error \"new_token\""));
  new_token->next = NULL;
  new_token->value = NULL;
  new_token->type = TOKEN_UNQUOTED_WORD;
  if (*(tc->head) == NULL)
    *(tc->head) = new_token;
  else
    tc->cur_token->next = new_token;
  tc->cur_token = new_token;
  return (0);
}

int set_token(t_token_context *tc, e_token_type type) {
  tc->cur_token->type = type;
  tc->cur_token->value =
      malloc(sizeof(char) * (tc->cur_str - tc->start_str + 1));
  if (!tc->cur_token->value)
    return (write_error("malloc error \"value\""));
  ft_memcpy(tc->cur_token->value, tc->start_str, tc->cur_str - tc->start_str);
  tc->cur_token->value[tc->cur_str - tc->start_str] = '\0';
  tc->start_str = tc->cur_str;
  return (0);
}

void process_space(t_token_context *tc) {
  while (ft_isspace(*tc->cur_str))
    tc->cur_str++;
  tc->start_str = tc->cur_str;
}

// unquoted string
int process_unquoted_word(t_token_context *tc) {
  if (create_token(tc) != 0)
    return (1);
  while (*tc->cur_str != '\0' && !ft_isspace(*tc->cur_str) &&
         *tc->cur_str != '|' && *tc->cur_str != '<' && *tc->cur_str != '>')
    tc->cur_str++;
  if (set_token(tc, TOKEN_UNQUOTED_WORD) != 0)
    return (1);
  return (0);
}

// quoted string
int process_quoted_word(t_token_context *tc) {
  char quote;
  e_token_type type;

  if (create_token(tc) != 0)
    return (1);
  quote = *tc->cur_str;
  if (quote == '\'')
    type = TOKEN_SINGLE_QUOTED_WORD;
  else if (quote == '"')
    type = TOKEN_DOUBLE_QUOTED_WORD;
  tc->cur_str++;
  tc->start_str = tc->cur_str;
  while (*tc->cur_str != '\0' && *tc->cur_str != quote)
    tc->cur_str++;
  if (*tc->cur_str == '\0')
    return (write_error("unclosed quotes"));
  if (set_token(tc, type) != 0)
    return (1);
  tc->cur_str++;
  tc->start_str = tc->cur_str;
  return (0);
}
