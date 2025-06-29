#include "ft_string.h"
#include "utils/env.h"
#include <stdlib.h>

void	set_env(void *content, void *ideal)
{
	t_env	*casted_content;
	t_env	*casted_ideal;

	casted_content = (t_env *)content;
	casted_ideal = (t_env *)ideal;
	free(casted_content->key);
	free(casted_content->value);
	casted_content->key = ft_strdup(casted_ideal->key);
	casted_content->value = ft_strdup(casted_ideal->value);
}
