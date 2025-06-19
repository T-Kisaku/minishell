#include <stdlib.h>

void	free_and_null(void **ptr)
{
	if (!ptr || !*ptr)
		return ;
	free(*ptr);
	ptr = NULL;
}
