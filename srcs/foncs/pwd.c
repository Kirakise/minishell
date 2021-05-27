#include "../../includes/minishell.h"

extern t_shell	g_shell;

void	pwd(void)
{
	char	*s;

	s = malloc(256);
	getcwd(s, 255);
	if (s)
	{
		write(g_shell.fd_1, s, ft_strlen(s));
		write(g_shell.fd_1, "\n", 1);
		exit(0);
	}
	dup2(g_shell.tmp_fd_1, 1);
	ft_putstr_nl("Error with pwd!\n");
	exit(-1);
}
