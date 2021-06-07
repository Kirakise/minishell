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

int	ft_exit(t_cmd **cmd, int status)
{
	free_cmd(cmd);
	history_free(&g_shell.hist);
	while (1);
	exit(status);
}

static void	exit_puterr(t_cmd **cmd, char *str)
{
	ft_putstr("minishell: exit: ");
	ft_putstr(str);
	ft_putstr_nl(": numeric argument required");
	ft_exit(cmd, 255);
}

void	sh_exit(t_cmd **cmd, int j)
{
	int	i;
	int	err;

	ft_putstr_nl("exit");
	i = 1;
	err = 0;
	if (j > 0 && cmd[j - 1]->pipe)
		return ;
	if (cmd[j]->args[i] && !ft_strcmp(cmd[j]->args[i], "--"))
		i++;
	if (!cmd[j]->args[i])
		ft_exit(cmd, 0);
	check_validity(cmd[j]->args[i], &err);
	if (err)
		exit_puterr(cmd, cmd[j]->args[i]);
	if (!cmd[j]->args[i + 1])
		ft_exit(cmd, ft_atoi(cmd[j]->args[i]));
	i++;
	while (cmd[j]->args[i] && !err)
	{
		check_validity(cmd[j]->args[i], &err);
		i++;
	}
	ft_putstr_nl("minishell: exit: too many arguments");
	g_shell.status = 1;
}
