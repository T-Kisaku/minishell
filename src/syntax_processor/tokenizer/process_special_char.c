#include <stdbool.h>
#include "syntax_processor/tokenizer.h"

static t_error *process_less_than(t_token_context *ctx);
static t_error *process_greater_than(t_token_context *ctx);

t_error *process_special_char(t_token_context *ctx) {
  if (*ctx->cur_str == '<')
    return (process_less_than(ctx));
  else if (*ctx->cur_str == '>')
    return (process_greater_than(ctx));
  else if (*ctx->cur_str == '|') {
    ctx->cur_str++;
    return (extract_and_add_token(ctx, TOKEN_PIPE));
  }
  return NULL;
}

// "<" or "<<"
static t_error *process_less_than(t_token_context *ctx) {
  ctx->cur_str++;
  if (*ctx->cur_str != '<')
    return (extract_and_add_token(ctx, TOKEN_REDIR_INPUT));
  else if (*ctx->cur_str == '<') {
    ctx->cur_str++;
    return (extract_and_add_token(ctx, TOKEN_REDIR_HERE_DOC));
  }
  return NULL;
}

//">" or ">>"
static t_error *process_greater_than(t_token_context *ctx) {
  ctx->cur_str++;
  if (*ctx->cur_str != '>')
    return (extract_and_add_token(ctx, TOKEN_REDIR_OUTPUT));
  else if (*ctx->cur_str == '>') {
    ctx->cur_str++;
    return (extract_and_add_token(ctx, TOKEN_REDIR_APPEND));
  }
  return NULL;
}
bool is_special_char(char c) { return c == '|' || c == '<' || c == '>'; };
