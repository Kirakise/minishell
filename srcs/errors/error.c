#include "../../includes/minishell.h"

extern t_shell	g_shell;

void	malloc_err(void)
{
	write(g_shell.tmp_fd_1, "malloc error!\n", 14);
	exit(-30);
}

void	ft_puterr(char *program_name, char *arg, int status)
{
	g_shell.status = status;
	ft_putstr(program_name);
	ft_putstr(": ");
	ft_putstr(arg);
	ft_putstr(": ");
	ft_putstr_nl(strerror(errno));
}
