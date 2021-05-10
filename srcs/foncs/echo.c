#include "../../includes/minishell.h"
#include "../../includes/libft.h"

extern t_shell	g_shell;

void	ft_echo(t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->args[i] && cmd->args[i + 1])
	{
		write(g_shell.fd_1, cmd->args[i], ft_strlen(cmd->args[i]));
		write(1, " ", 1);
		i++;
	}
	if (cmd->args[i])
		write(g_shell.fd_1, cmd->args[i], ft_strlen(cmd->args[i]));
	write(g_shell.fd_1, "\n", 1);
	exit(0);
}
