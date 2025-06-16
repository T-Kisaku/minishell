#include "error.h"
#include "exit_status.h"
#include "utils/utils.h"
#include "utils/ms_string.h"
#include "syntax_processor/tokenizer.h"

static int tokenize(t_list **head, char *string);
static void init_token_context(t_token_context *ctx, t_list **head,
                               char *string);
static int tokenize_loop(t_token_context *ctx);
static int add_eof_token(t_token_context *ctx);

int str_to_token(char *input_str, t_list **token_list_ptr) {
  t_token_context ctx;
  if (input_str == NULL) {
    dev_error();
    return (EXIT_INTERNAL_ERR);
  }
  if (tokenize(token_list_ptr, input_str) != EXIT_OK) {
    free_token_list(token_list_ptr);
    return (EXIT_INTERNAL_ERR);
  }
  return EXIT_OK;
}

static int tokenize(t_list **head, char *string) {
  t_token_context ctx;

  init_token_context(&ctx, head, string);
  if (tokenize_loop(&ctx) != EXIT_OK)
    return (EXIT_INTERNAL_ERR);
  if (add_eof_token(&ctx) != EXIT_OK)
    return (EXIT_INTERNAL_ERR);
  return (EXIT_OK);
}

static void init_token_context(t_token_context *ctx, t_list **head,
                               char *string) {
  ctx->head = head;
  ctx->cur_token = NULL;
  ctx->start_str = string;
  ctx->cur_str = string;
}

static int tokenize_loop(t_token_context *ctx) {
  while (*ctx->cur_str) {
    if (ft_isspace(*ctx->cur_str))
      process_space(ctx);
    else if (*ctx->cur_str == '\'' || *ctx->cur_str == '"') {
      if (process_quoted_word(ctx) != 0)
        return (1);
    } else if (*ctx->cur_str == '<' || *ctx->cur_str == '>' ||
               *ctx->cur_str == '|') {
      if (process_special_char(ctx) != 0)
        return (1);
    } else {
      if (process_unquoted_word(ctx) != 0)
        return (1);
    }
  }
  return (0);
}

static int add_eof_token(t_token_context *ctx) {
  if (create_token(ctx) != 0)
    return (1);
  if (set_token(ctx, TOKEN_EOF) != 0)
    return (1);
  return (0);
}
