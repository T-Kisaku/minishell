#include "syntax_processor/tokenizer.h"
#include "utils/ms_string.h"
#include "utils/utils.h"
int create_token(t_token_context *ctx);
int set_token(t_token_context *ctx, t_token_type type);
void process_space(t_token_context *ctx);
int process_quoted_word(t_token_context *ctx);
int process_unquoted_word(t_token_context *ctx);

int create_token(t_token_context *ctx) {
  t_list *new_token;
  t_token_content *new_token_content;

  new_token = malloc(sizeof(t_list));
  if (!new_token)
    return (write_error("malloc error \"new_token\""));
  new_token->next = NULL;
  new_token->content = malloc(sizeof(t_token_content));
  if (!new_token->content)
    return (write_error("malloc_error \"new_token->content\""));
  new_token_content = new_token->content;
  new_token_content->value = NULL;
  new_token_content->type = TOKEN_UNQUOTED_WORD;
  if (*(ctx->head) == NULL)
    *(ctx->head) = new_token;
  else
    ctx->cur_token->next = new_token;
  ctx->cur_token = new_token;
  return (0);
}

int set_token(t_token_context *ctx, t_token_type type) {
  t_token_content *cur_token_content;

  cur_token_content = ctx->cur_token->content;
  cur_token_content->type = type;
  cur_token_content->value =
      malloc(sizeof(char) * (ctx->cur_str - ctx->start_str + 1));
  if (!cur_token_content->value)
    return (write_error("malloc error \"value\""));
  ft_memcpy(cur_token_content->value, ctx->start_str,
            ctx->cur_str - ctx->start_str);
  cur_token_content->value[ctx->cur_str - ctx->start_str] = '\0';
  ctx->start_str = ctx->cur_str;
  return (0);
}

void process_space(t_token_context *ctx) {
  while (ms_isspace(*ctx->cur_str))
    ctx->cur_str++;
  ctx->start_str = ctx->cur_str;
}

// unquoted string
int process_unquoted_word(t_token_context *ctx) {
  if (create_token(ctx) != 0)
    return (1);
  while (*ctx->cur_str != '\0' && !ms_isspace(*ctx->cur_str) &&
         *ctx->cur_str != '|' && *ctx->cur_str != '<' && *ctx->cur_str != '>')
    ctx->cur_str++;
  if (set_token(ctx, TOKEN_UNQUOTED_WORD) != 0)
    return (1);
  return (0);
}

// quoted string
int process_quoted_word(t_token_context *ctx) {
  char quote;
  t_token_type type;

  if (create_token(ctx) != 0)
    return (1);
  quote = *ctx->cur_str;
  if (quote == '\'')
    type = TOKEN_SINGLE_QUOTED_WORD;
  else if (quote == '"')
    type = TOKEN_DOUBLE_QUOTED_WORD;
  ctx->cur_str++;
  ctx->start_str = ctx->cur_str;
  while (*ctx->cur_str != '\0' && *ctx->cur_str != quote)
    ctx->cur_str++;
  if (*ctx->cur_str == '\0')
    return (write_error("unclosed quotes"));
  if (set_token(ctx, type) != 0)
    return (1);
  ctx->cur_str++;
  ctx->start_str = ctx->cur_str;
  return (0);
}
