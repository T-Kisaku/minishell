#include "ft_printf.h"
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

void	print_child_signal_message(int status)
{
	int	sig;

	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGQUIT)
		{
			if (WCOREDUMP(status))
				ft_dprintf(STDERR_FILENO, "Quit (core dumped)\n");
			else
				ft_dprintf(STDERR_FILENO, "Quit\n");
		}
	}
}
