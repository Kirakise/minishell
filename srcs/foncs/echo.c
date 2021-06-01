#include "../../includes/minishell.h"

extern t_shell	g_shell;

static int	is_n(char *str)
{
	if (ft_strncmp(str, "-n", 2))
		return (0);
	str += 2;
	while (*str == 'n')
		str++;
	if (!*str)
		return (1);
	return (0);
}

void	ft_echo(t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->args[i] && is_n(cmd->args[i]))
		i++;
	while (cmd->args[i])
	{
		write(g_shell.fd_1, cmd->args[i], ft_strlen(cmd->args[i]));
		i++;
		if (cmd->args[i])
			write(g_shell.fd_1, " ", 1);
	}
	if (!cmd->args[1] || (cmd->args[1] && !is_n(cmd->args[1])))
		write(g_shell.fd_1, "\n", 1);
	exit(0);
}
