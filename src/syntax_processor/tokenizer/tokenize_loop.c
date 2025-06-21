#include "token.h"
#include "exit_status.h"
#include "error.h"
#include "utils/ms_string.h"
#include "syntax_processor/tokenizer.h"

static void process_space(t_token_context *ctx);
static t_error *process_unquoted_word(t_token_context *ctx);
static t_error *process_quoted_word(t_token_context *ctx);

t_error *tokenize_loop(t_token_context *ctx) {
  t_error *error;
  error = NULL;
  while (*ctx->cur_str) {
    process_space(ctx);
    error = process_special_char(ctx);
    if (is_error(error))
      return error;
    error = process_quoted_word(ctx);
    if (is_error(error))
      return error;
    error = process_unquoted_word(ctx);
    if (is_error(error))
      return error;
  }
  return error;
}

static void process_space(t_token_context *ctx) {
  while (ms_isspace(*ctx->cur_str))
    ctx->cur_str++;
  ctx->start_str = ctx->cur_str;
}

// unquoted string
static t_error *process_unquoted_word(t_token_context *ctx) {
  if (*ctx->cur_str == '\0' || ms_isspace(*ctx->cur_str) ||
      is_special_char(*ctx->cur_str))
    return NULL;
  while (*ctx->cur_str != '\0' && !ms_isspace(*ctx->cur_str) &&
         !is_special_char(*ctx->cur_str))
    ctx->cur_str++;
  return extract_and_add_token(ctx, TOKEN_UNQUOTED_WORD);
}

// quoted string
static t_error *process_quoted_word(t_token_context *ctx) {
  char quote;
  t_token_type type;
  t_error *error;
  error = NULL;

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
  /* if (*ctx->cur_str == '\0') { */
  /*   user_error("minishell: syntax error: unclosed quote\n"); */
  /*   return (EXIT_USER_ERR); */
  /* } */
  error = extract_and_add_token(ctx, type);
  if (is_error(error))
    return error;
  ctx->cur_str++;
  ctx->start_str = ctx->cur_str;
  return (error);
}
