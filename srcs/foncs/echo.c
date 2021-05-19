#include "../../includes/minishell.h"

extern t_shell	g_shell;

void	ft_echo(t_cmd *cmd)
{
	int	i;

	i = 1;
	if (cmd->args[i] && !ft_strcmp(cmd->args[i], "-n"))
		i++;
	while (cmd->args[i] && cmd->args[i + 1])
	{
		write(g_shell.fd_1, cmd->args[i], ft_strlen(cmd->args[i]));
		write(1, " ", 1);
		i++;
	}
	if (cmd->args[i])
		write(g_shell.fd_1, cmd->args[i], ft_strlen(cmd->args[i]));
	if (!cmd->args[1] || (cmd->args[1] && ft_strcmp(cmd->args[1], "-n")))
		write(g_shell.fd_1, "\n", 1);
	exit(0);
}
