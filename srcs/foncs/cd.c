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
	free(s);
	if (error != 0)
	{
		g_shell.status = 1;
		s = strerror(errno);
		ft_putstr_nl(s);
	}
}

void	tmp2(t_cmd *cmd)
{
	int		error;
	char	*s;

	changeold();
	error = chdir(cmd->args[1]);
	if (error != 0)
	{
		g_shell.status = 1;
		s = strerror(errno);
		ft_putstr_nl(s);
	}
}

void	tmp4(void)
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
	free(s);
	if (error != 0)
	{
		g_shell.status = 1;
		s = strerror(errno);
		ft_putstr_nl(s);
	}
}

void	tmp3(t_cmd *cmd)
{
	int		error;
	char	*s;

	changeold();
	error = chdir(cmd->args[1]);
	if (error != 0)
	{
		g_shell.status = 1;
		s = strerror(errno);
		ft_putstr_nl(s);
	}
}

void	cd(t_cmd *cmd)
{
	if (!(cmd->args[1]) || !ft_strcmp(cmd->args[1], "~"))
		tmp1();
	else if (!ft_strcmp(cmd->args[1], "-"))
		tmp4();
	else if (cmd->args[1][0] == '/')
		tmp2(cmd);
	else
		tmp3(cmd);
}
