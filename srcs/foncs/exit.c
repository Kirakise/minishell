#include "../../includes/minishell.h"

extern t_shell	g_shell;

static void	check_validity(char *str, int *err)
{
	int	i;

	i = 0;
	if ((str && (str[i] == '-' || str[i] == '+') && ft_isdigit(str[i + 1])))
		i++;
	while (str && str[i] && ft_isdigit(str[i]))
		i++;
	if (str && str[i])
		*err = 255;
}

static void	exit_puterr(char *str)
{
	ft_putstr("exit: ");
	ft_putstr(str);
	ft_putstr_nl(": numeric argument required");
	exit(255);
}

void	sh_exit(t_cmd *cmd)
{
	int	i;
	int	err;

	i = 1;
	err = 0;
	if (cmd->args[i] && !ft_strcmp(cmd->args[i], "--"))
		i++;
	if (!cmd->args[i])
		exit(0);
	check_validity(cmd->args[i], &err);
	if (err)
		exit_puterr(cmd->args[i]);
	if (!cmd->args[i + 1])
		exit(ft_atoi(cmd->args[i]));
	i++;
	while (cmd->args[i] && !err)
	{
		check_validity(cmd->args[i], &err);
		i++;
	}
	ft_putstr_nl("exit: too many arguments");
	g_shell.status = 1;
}
