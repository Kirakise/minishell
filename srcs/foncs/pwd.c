#include "../../includes/minishell.h"

extern t_shell	g_shell;

void	pwd(t_cmd *cmd)
{
	char	*s;

	if (cmd->args[1])
	{
		write(g_shell.tmp_fd_1, "too many arguments\n", 20);
		exit(1);
	}
	s = malloc(256);
	getcwd(s, 255);
	if (s)
	{
		write(g_shell.fd_1, s, ft_strlen(s));
		write(g_shell.fd_1, "\n", 1);
		exit(0);
	}
	exit(-1);
}
