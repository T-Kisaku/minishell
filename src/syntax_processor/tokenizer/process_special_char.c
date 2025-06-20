#include "syntax_processor/tokenizer.h"
#include "exit_status.h"

static int process_less_than(t_token_context *ctx);
static int process_greater_than(t_token_context *ctx);

int process_special_char(t_token_context *ctx) {
  if (*ctx->cur_str == '<')
    return (process_less_than(ctx));
  else if (*ctx->cur_str == '>')
    return (process_greater_than(ctx));
  else if (*ctx->cur_str == '|') {
    ctx->cur_str++;
    return (extract_and_add_token(ctx, TOKEN_PIPE));
  }
  return EXIT_OK;
}

// "<" or "<<"
static int process_less_than(t_token_context *ctx) {
  ctx->cur_str++;
  if (*ctx->cur_str != '<')
    return (extract_and_add_token(ctx, TOKEN_REDIR_INPUT));
  else if (*ctx->cur_str == '<') {
    ctx->cur_str++;
    return (extract_and_add_token(ctx, TOKEN_REDIR_HERE_DOC));
  }
  return EXIT_OK;
}

//">" or ">>"
static int process_greater_than(t_token_context *ctx) {
  ctx->cur_str++;
  if (*ctx->cur_str != '>')
    return (extract_and_add_token(ctx, TOKEN_REDIR_OUTPUT));
  else if (*ctx->cur_str == '>') {
    ctx->cur_str++;
    return (extract_and_add_token(ctx, TOKEN_REDIR_APPEND));
  }
  return EXIT_OK;
}
int is_special_char(char c) { return c == '|' || c == '<' || c == '>'; };
