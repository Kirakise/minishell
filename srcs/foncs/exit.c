#include "../../includes/minishell.h"

extern t_shell	g_shell;

void	sh_exit(t_cmd *cmd)
{
	int	i;

	if (!cmd->args[1])
		exit(0);
	if (cmd->args[1] && cmd->args[2])
	{
		ft_putstr_nl("exit: too many arguments");
		g_shell.status = 1;
		return ;
	}
	if (!ft_strcmp(cmd->args[1], "--"))
		exit(0);
	i = 0;////here
	if ((cmd->args[1][i] == '-' || cmd->args[1][i] == '+')
			&& ft_isdigit(cmd->args[1][i + 1]))
		i++;
	while (cmd->args[1][i] && ft_isdigit(cmd->args[1][i]))
		i++;
	if (cmd->args[1][i])
	{
		ft_putstr("exit: ");
		ft_putstr(cmd->args[1]);
		ft_putstr_nl(": numeric argument required");
		exit(255);
	}
	exit(ft_atoi(cmd->args[1]));
}
