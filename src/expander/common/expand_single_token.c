
#include "expander.h"
#include <stdio.h>

int			expand_single_token(t_token *content);
static void	init_expansion_context(t_expansion_context *ctx,
									t_token *content);
static int	process_expansion_core(t_expansion_context *ctx,
									e_expander_mode mode);
static void	set_dollar_type(t_expansion_context *ctx);

//ワイルドカードの扱いでunquotedとdobule_quotedで差が出るが、ボーナス内容なので一旦スルー
int	expand_single_token(t_token *content)
{
	t_expansion_context	ctx;

	if (!content)
		return (1);
	init_expansion_context(&ctx, content);
	if (process_expansion_core(&ctx, MODE_CALCULATE) != 0)
		return (1);
	ctx.cur_pos = (char *)ctx.input;
	ctx.index = 0;
	if (process_expansion_core(&ctx, MODE_SET_VALUE) != 0)
		return (1);
	free(content->value);
	content->value = ctx.output;
	return (0);
}

static void	init_expansion_context(t_expansion_context *ctx,
									t_token *content)
{
	t_token	*token_content;

	token_content = content;
	ctx->input = token_content->value;
	ctx->output = NULL;
	ctx->cur_pos = token_content->value;
	ctx->next_pos = NULL;
	ctx->index = 0;
	ctx->required_len = 0;
	ctx->in_single_quote = 0;
	ctx->cur_dollar_type = DOLLAR_LITERAL;
	ctx->variable = NULL;
}

static int process_expansion_core(t_expansion_context *ctx,
                                  e_expander_mode mode) {
  if (mode == MODE_SET_VALUE) {
    ctx->output = malloc(sizeof(char) * (ctx->required_len + 1));
    if (!ctx->output)
      return (1);
  }
  while (*ctx->cur_pos) {
    if (!ctx->in_single_quote && *ctx->cur_pos == '$') {
      set_dollar_type(ctx);
      if (process_expansion_core_core(ctx, mode) != 0)
        return (1);
    } else {
      if (*ctx->cur_pos == '\'')
        ctx->in_single_quote = (ctx->in_single_quote + 1) % 2;
      if (mode == MODE_SET_VALUE)
        ft_memcpy(&ctx->output[ctx->index], ctx->cur_pos, 1);
      ctx->index++;
      ctx->cur_pos++;
    }
  }
  if (mode == MODE_CALCULATE)
    ctx->required_len = ctx->index;
  else if (mode == MODE_SET_VALUE)
    ctx->output[ctx->index] = '\0';
  return (0);
}

static void set_dollar_type(t_expansion_context *ctx) {
  ctx->cur_pos++;
  ctx->next_pos = ctx->cur_pos;
  ctx->next_pos++;
  if (*ctx->cur_pos == '?' || *ctx->cur_pos == '$' || *ctx->cur_pos == '!' ||
      *ctx->cur_pos == '0' || ft_isdigit(*ctx->cur_pos) ||
      *ctx->cur_pos == '$' || *ctx->cur_pos == '*' || *ctx->cur_pos == '@' ||
      (*ctx->cur_pos == '_' && *ctx->next_pos != '_' &&
       !ft_isalnum(*ctx->next_pos)) ||
      *ctx->cur_pos == '-')
    ctx->cur_dollar_type = DOLLAR_SPECIAL;
  else if (ft_isalpha(*ctx->cur_pos) || *ctx->cur_pos == '_')
    ctx->cur_dollar_type = DOLLAR_VARIABLE;
  else
    ctx->cur_dollar_type = DOLLAR_LITERAL;
}
