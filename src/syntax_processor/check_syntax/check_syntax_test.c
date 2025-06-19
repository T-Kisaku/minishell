#include "check_syntax.h"
#include "syntax_processor.h"
#include "token.h"
#include <stdio.h>
int	check(char *s);

int	main(void)
{
	check("hello > < world ");
	// check("|");
	// check("<");
	return (0);
}

int	check(char *s)
{
	t_list	*list;

	list = tokenizer(s);
	if (!list)
	{
		printf("tokenizer_error\n");
		return (1);
	}
	if (check_syntax(list) != 0)
	{
		printf("check_syntax_error\n");
		return (1);
	}
	printf("OK\n");
	return (0);
}
