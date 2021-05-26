#include "../../includes/minishell.h"

extern t_shell	g_shell;

void	envprint(int regime)
{
	int	i;

	i = 0;
	while (g_shell.env[i])
	{
		if (regime)
			write(g_shell.fd_1, "declare -x ", 12);
		write(g_shell.fd_1, g_shell.env[i], ft_strlen(g_shell.env[i]));
		write(g_shell.fd_1, "\n", 1);
		i++;
	}
	exit(0);
}
