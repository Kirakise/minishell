#include "../../includes/minishell.h"

extern t_shell	g_shell;

void	tmp1(void)
{
	int		error;
	char	*s;

	changeold();
	s = find_var("HOME");
	error = 0;
	if (!s)
	{
		write(g_shell.tmp_fd_1, "HOME not set\n", 14);
		g_shell.status = 1;
		return ;
	}
	else if (s[0] != 0)
		error = chdir((s));
	if (error != 0)
		ft_puterr("cd", s, 1);
	free(s);
}

void	tmp2(t_cmd *cmd)
{
	int		error;

	changeold();
	error = chdir(cmd->args[1]);
	if (error != 0)
		ft_puterr("cd", cmd->args[1], 1);
}

void	tmp3(void)
{
	int		error;
	char	*s;

	s = find_var("OLDPWD");
	error = 0;
	if (!s)
	{
		write(g_shell.tmp_fd_1, "OLDPWD not set\n", 14);
		g_shell.status = 1;
		return ;
	}
	else if (s[0] != 0)
		error = chdir((s));
	if (error != 0)
		ft_puterr("cd", s, 1);
	free(s);
}

void	cd(t_cmd *cmd)
{
	if (!(cmd->args[1]) || !ft_strcmp(cmd->args[1], "~"))
		tmp1();
	else if (!ft_strcmp(cmd->args[1], "-"))
		tmp3();
	else
		tmp2(cmd);
}
