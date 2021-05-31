#include "../../includes/minishell.h"

extern t_shell	g_shell;

void	malloc_err(void)
{
	write(g_shell.tmp_fd_1, "malloc error!\n", 15);
	exit(-30);
}
