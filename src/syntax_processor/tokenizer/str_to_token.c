#include "error.h"
#include "exit_status.h"
#include "syntax_processor/tokenizer.h"

static int tokenize(t_list **head, char *string);

int str_to_token(char *input_str, t_list **token_list_ptr) {
  if (input_str == NULL) {
    dev_error();
    return (EXIT_INTERNAL_ERR);
  }
  if (tokenize(token_list_ptr, input_str) != EXIT_OK) {
    lstclear_token(token_list_ptr);
    return (EXIT_INTERNAL_ERR);
  }
  return EXIT_OK;
}

static int tokenize(t_list **head, char *string) {
  t_token_context ctx;

  ctx.head = head;
  ctx.start_str = string;
  ctx.cur_str = string;
  return tokenize_loop(&ctx);
}
