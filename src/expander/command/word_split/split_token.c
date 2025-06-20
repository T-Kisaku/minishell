#include "expander.h"
#include "utils/ms_string.h"

int split_token(t_list *token_node, int word_count);
static int init_split_token_context(t_split_token_context *ctx,
                                    t_list *token_node);
static int generate_value(t_split_token_context *ctx);
int generate_token(t_split_token_context *ctx);

int split_token(t_list *token, int word_count) {
  t_split_token_context ctx;
  t_token *token_content;

  init_split_token_context(&ctx, token);
  token_content = (t_token *)token->content;
  free(token_content->value);
  if (generate_value(&ctx) != 0) {
    free(ctx.original);
    return (1);
  }
  while (--word_count) {
    if (generate_token(&ctx) != 0) {
      free(ctx.original);
      return (1);
    }
  }
  free(ctx.original);
  return (0);
}

static int init_split_token_context(t_split_token_context *ctx,
                                    t_list *token_node) {
  t_token *cur_token_content;

  ctx->cur = token_node;
  ctx->next = token_node->next;
  ctx->tmp = NULL;
  cur_token_content = (t_token *)ctx->cur->content;
  ctx->original = ft_strdup(cur_token_content->value);
  if (!ctx->original)
    return (1);
  ctx->start_str = ctx->original;
  ctx->cur_str = ctx->original;
  return (0);
}

static int generate_value(t_split_token_context *ctx) {
  t_token *cur_token_content;

	while (*ctx->cur_str && ms_isspace(*ctx->cur_str))
		ctx->cur_str++;
	ctx->start_str = ctx->cur_str;
	while (*ctx->cur_str && !ms_isspace(*ctx->cur_str))
		ctx->cur_str++;
	cur_token_content = (t_token*)ctx->cur->content; 
	cur_token_content->value = malloc(sizeof(char) * (ctx->cur_str
				- ctx->start_str + 1));
	if (!cur_token_content->value)
		return (1);
	ft_memcpy((char *)cur_token_content->value, (char *)ctx->start_str,
			ctx->cur_str - ctx->start_str);
	cur_token_content->value[ctx->cur_str - ctx->start_str] = '\0';
	return (0);
}

int generate_token(t_split_token_context *ctx) {
  t_token *cur_token_content;

  ctx->tmp = malloc(sizeof(t_list));
  if (!ctx->tmp)
    return (1);
  ctx->cur->next = ctx->tmp;
  ctx->tmp->next = ctx->next;
  ctx->cur = ctx->tmp;
  ctx->next = ctx->cur->next;
  ctx->cur->content = malloc(sizeof(t_token));
  if (!ctx->cur->content)
    return (1);
  cur_token_content = (t_token *)ctx->cur->content;
  cur_token_content->type = TOKEN_UNQUOTED_WORD;
  if (generate_value(ctx) != 0)
    return (1);
  return (0);
}
