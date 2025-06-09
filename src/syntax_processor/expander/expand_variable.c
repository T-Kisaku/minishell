#include "../../../include/expander.h"
#include "../../../include/token.h"
#include "../../../include/utils.h"
#include "../../../libft/libft.h"

int			expand_variable(t_expansion_context *ctx);
int			expand_special(t_expansion_context *ctx);
static int	set_temp(t_expansion_context *ctx, char *str, e_mode_set_temp mode);

int	expand_variable(t_expansion_context *ctx)
{
	char	*start;
	char	*tmp;

	start = ctx->cur_pos;
	if (*ctx->cur_pos == '_' || ft_isalpha(*ctx->cur_pos))
		ctx->cur_pos++;
	else
		return (1);
	while (*ctx->cur_pos == '_' || ft_isalnum(*ctx->cur_pos))
		ctx->cur_pos++;
	tmp = ft_strndup(start, ctx->cur_pos - start);
	if (!tmp)
		return (1);
	ctx->variable = getenv(tmp);
	free(tmp);
	if (!ctx->variable)
	{
		ctx->variable = malloc(sizeof(char));
		if (!ctx->variable)
			return (1);
		*ctx->variable = '\0';
	}
	else
	{
		ctx->variable = ft_strdup(ctx->variable);
		if (!ctx->variable)
			return (1);
	}
	return (0);
}

int	expand_special(t_expansion_context *ctx)
{
	if (*ctx->cur_pos == '?') //後で実装
		return (0);
	else if (*ctx->cur_pos == '$') //後で実装
		return (0);
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
	else if (*ctx->cur_pos == '_' && *ctx->next_pos != '_'
			&& !ft_isalnum(*ctx->next_pos))
		return (set_temp(ctx, "", SET_MODE_NORMAL));
	else if (*ctx->cur_pos == '-')
		return (set_temp(ctx, "", SET_MODE_NORMAL));
	return (1);
}

static int	set_temp(t_expansion_context *ctx, char *str, e_mode_set_temp mode)
{
	if (mode == SET_MODE_FIGURE)
		while (ft_isdigit((int)*ctx->cur_pos))
			ctx->cur_pos++;
	if (str)
	{
		ctx->variable = ft_strdup(str);
		if (!ctx->variable)
			return (1);
		if (mode == SET_MODE_NORMAL)
			ctx->cur_pos++;
		return (0);
	}
	else
		return (1);
}
