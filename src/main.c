#include "minishell.h"
#include <stdlib.h>

int main(int argc, char** argv)
{
	t_data data;
	data.lexered = NULL;
	data.parsered = NULL;
	data.lexered = lexer(argv);
	data.parsered = (data.lexered);
	executor(data.parsered);
	cleanup(data);
}