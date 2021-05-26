#include "../../includes/minishell.h"

extern t_shell	g_shell;

void	sh_exit(t_cmd *cmd)
{
	int	i;

	if (cmd->args[1] && cmd->args[2])
	{
		ft_putstr_nl("exit: too many arguments");
		g_shell.status = 1;
	}
	else if (cmd->args[1])
	{
		i = 0;
		while (cmd->args[1][i] && ft_isdigit(cmd->args[1][i]))
			i++;
		if (cmd->args[1][i])
		{
			ft_putstr("exit: ");
			ft_putstr(cmd->args[1]);
			ft_putstr_nl(": numeric argument required");
			g_shell.status = 255;
		}
		else
			exit(ft_atoi(cmd->args[1]));
	}
	else
		exit(0);
}
