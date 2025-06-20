#include "expander.h"
#include "utils/ms_string.h"
#include "error.h"
#include "exit_status.h"

t_error *expand_variable(t_expansion_context *ctx);
t_error *expand_special(t_expansion_context *ctx);
static t_error *set_temp(t_expansion_context *ctx, char *str,
                         e_mode_set_temp mode);

t_error *expand_variable(t_expansion_context *ctx) {
  char *start;
  char *tmp;

  start = ctx->cur_pos;
  if (*ctx->cur_pos == '_' || ft_isalpha(*ctx->cur_pos))
    ctx->cur_pos++;
  else
    return new_error(EXIT_INTERNAL_ERR, "$[_a-zA-Z]");
  while (*ctx->cur_pos == '_' || ft_isalnum(*ctx->cur_pos))
    ctx->cur_pos++;
  tmp = ms_strndup(start, ctx->cur_pos - start);
  if (!tmp)
    return new_error(EXIT_INTERNAL_ERR, "MALLOC ERRO");
  ctx->variable = getenv(tmp);
  free(tmp);
  if (!ctx->variable) {
    ctx->variable = malloc(sizeof(char));
    if (!ctx->variable)
      return new_error(EXIT_INTERNAL_ERR, "MALLOC ERRO");
    *ctx->variable = '\0';
  } else {
    ctx->variable = ft_strdup(ctx->variable);
    if (!ctx->variable)
      return new_error(EXIT_INTERNAL_ERR, "MALLOC ERRO");
  }
  return (NULL);
}

t_error *expand_special(t_expansion_context *ctx) {
  if (*ctx->cur_pos == '?') // 後で実装
    return (NULL);
  else if (*ctx->cur_pos == '$') // 後で実装
    return (NULL);
  else if (*ctx->cur_pos == '!')
    return (set_temp(ctx, "", SET_MODE_NORMAL));
  else if (*ctx->cur_pos == '0')
    return (set_temp(ctx, "minishell", SET_MODE_NORMAL));
  else if (ft_isdigit(*ctx->cur_pos))
    return (set_temp(ctx, "", SET_MODE_FIGURE));
  else if (*ctx->cur_pos == '#')
    return (set_temp(ctx, "0", SET_MODE_NORMAL));
  else if (*ctx->cur_pos == '*')
    return (set_temp(ctx, "", SET_MODE_NORMAL));
  else if (*ctx->cur_pos == '@')
    return (set_temp(ctx, "", SET_MODE_NORMAL));
  else if (*ctx->cur_pos == '_' && *ctx->next_pos != '_' &&
           !ft_isalnum(*ctx->next_pos))
    return (set_temp(ctx, "", SET_MODE_NORMAL));
  else if (*ctx->cur_pos == '-')
    return (set_temp(ctx, "", SET_MODE_NORMAL));
  return new_error(EXIT_INTERNAL_ERR, "I don't know why bro");
}

static t_error *set_temp(t_expansion_context *ctx, char *str,
                         e_mode_set_temp mode) {
  if (mode == SET_MODE_FIGURE)
    while (ft_isdigit((int)*ctx->cur_pos))
      ctx->cur_pos++;
  if (!str) {
    return new_error(EXIT_INTERNAL_ERR, "str is not good bro");
  }
  ctx->variable = ft_strdup(str);
  if (!ctx->variable)
    return new_error(EXIT_INTERNAL_ERR, "MALLOC ERRO");
  if (mode == SET_MODE_NORMAL)
    ctx->cur_pos++;
  return (NULL);
}
