#include "token.h"
#include "exit_status.h"
#include "error.h"
#include "utils/ms_string.h"
#include "syntax_processor/tokenizer.h"

static void process_space(t_token_context *ctx);
static int process_unquoted_word(t_token_context *ctx);
static int process_quoted_word(t_token_context *ctx);

int tokenize_loop(t_token_context *ctx) {
  int exit_code;
  exit_code = EXIT_OK;
  while (*ctx->cur_str) {
    process_space(ctx);
    exit_code = process_special_char(ctx);
    if (exit_code != EXIT_OK)
      return exit_code;
    exit_code = process_quoted_word(ctx);
    if (exit_code != EXIT_OK)
      return exit_code;
    exit_code = process_unquoted_word(ctx);
    if (exit_code != EXIT_OK)
      return exit_code;
  }
  return (EXIT_OK);
}

static void process_space(t_token_context *ctx) {
  while (ms_isspace(*ctx->cur_str))
    ctx->cur_str++;
  ctx->start_str = ctx->cur_str;
}

// unquoted string
static int process_unquoted_word(t_token_context *ctx) {
  if (*ctx->cur_str == '\0' || ms_isspace(*ctx->cur_str) ||
      is_special_char(*ctx->cur_str))
    return (EXIT_OK);
  while (*ctx->cur_str != '\0' && !ms_isspace(*ctx->cur_str) &&
         !is_special_char(*ctx->cur_str))
    ctx->cur_str++;
  return extract_and_add_token(ctx, TOKEN_UNQUOTED_WORD);
}

// quoted string
static int process_quoted_word(t_token_context *ctx) {
  char quote;
  t_token_type type;

  quote = *ctx->cur_str;
  if (quote != '\'' && quote != '"')
    return (EXIT_OK);
  if (quote == '\'')
    type = TOKEN_SINGLE_QUOTED_WORD;
  else if (quote == '"')
    type = TOKEN_DOUBLE_QUOTED_WORD;
  ctx->cur_str++;
  ctx->start_str = ctx->cur_str;
  while (*ctx->cur_str != '\0' && *ctx->cur_str != quote)
    ctx->cur_str++;
  if (*ctx->cur_str == '\0') {
    user_error("minishell: syntax error: unclosed quote\n");
    return (EXIT_USER_ERR);
  }
  if (extract_and_add_token(ctx, type) != EXIT_OK)
    return (EXIT_INTERNAL_ERR);
  ctx->cur_str++;
  ctx->start_str = ctx->cur_str;
  return (EXIT_OK);
}
