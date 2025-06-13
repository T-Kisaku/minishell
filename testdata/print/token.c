#include <stdio.h>
#include "libft.h"
#include "token.h"

static const char *token_type_to_string(e_token_type type);

void print_token_list(t_list *token_list) {
  t_list *current = token_list;
  t_token_content *token;
  int token_count = 0;

  printf("=== Tokenization Results ===\n");
  while (current) {
    token = (t_token_content *)(current->content);
    printf("Token %d: '%s' -> %s\n", ++token_count, token->value,
           token_type_to_string(token->type));
    current = current->next;
  }
  printf("Total tokens: %d\n\n", token_count);
}

static const char *token_type_to_string(e_token_type type) {
  switch (type) {
  case TOKEN_UNQUOTED_WORD:
    return "UNQUOTED_WORD";
  case TOKEN_SINGLE_QUOTED_WORD:
    return "SINGLE_QUOTED_WORD";
  case TOKEN_DOUBLE_QUOTED_WORD:
    return "DOUBLE_QUOTED_WORD";
  case TOKEN_PIPE:
    return "PIPE";
  case TOKEN_REDIR_INPUT:
    return "REDIR_INPUT";
  case TOKEN_REDIR_OUTPUT:
    return "REDIR_OUTPUT";
  case TOKEN_REDIR_HERE_DOC:
    return "REDIR_HERE_DOC";
  case TOKEN_REDIR_APPEND:
    return "REDIR_APPEND";
  case TOKEN_EOF:
    return "EOF"; // for parser revive!
  default:
    return "UNKNOWN";
  }
}
