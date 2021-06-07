#include "../../includes/minishell.h"
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

extern t_shell	g_shell;

void	puterror(t_cmd *cmd, int regime)
{
	ft_putstr("minishell: ");
	ft_putstr(cmd->exec_name);
	if (regime == 1)
	{
		ft_putstr_nl(": is a directory");
		exit(126);
	}
	else if (regime == 2)
	{
		ft_putstr_nl(": Permission denied");
		exit(126);
	}
	else if (regime == 3)
	{
		ft_putstr_nl(": command not found");
		exit(127);
	}
	ft_putstr(": ");
	ft_putstr_nl(strerror(errno));
	exit(127);
}

void	checkinp(t_cmd *cmd)
{
	int			i;
	struct stat	tmp;

	if (ft_strchr('/', cmd->exec_name))
	{
		if (cmd->exec_name[0] == '/' || cmd->exec_name[0] == '.')
			i = stat(cmd->exec_name, &tmp);
		else
			i = stat(ft_strjoin_3(find_var("PWD"), "/", cmd->exec_name), &tmp);
		if (i == -1)
			puterror(cmd, 0);
		if (S_ISDIR(tmp.st_mode))
			puterror(cmd, 1);
		else if ((tmp.st_mode & S_IXUSR) == 0)
			puterror(cmd, 2);
	}
	else if (cmd->exec_name[0] == '\0' && !cmd->redir)
		puterror(cmd, 3);
	else if (cmd->exec_name[0] == '\0' && cmd->redir)
		exit(0);
}

int	do_exec(t_cmd *cmd)
{
	char		*s;
	int			i;
	char		**dirs;

	i = 0;
	checkinp(cmd);
	s = find_var("PATH");
	dirs = ft_split(s, ':');
	signal(SIGQUIT, SIG_DFL);
	while (dirs && dirs[i])
	{
		s = ft_strjoin(dirs[i], "/");
		s = ft_strjoin(s, cmd->exec_name);
		execve(s, cmd->args, g_shell.env);
		i++;
	}
	if (ft_strchr('/', cmd->exec_name))
		execve(cmd->exec_name, cmd->args, g_shell.env);
	dup2(g_shell.tmp_fd_1, 1);
	if (cmd->exec_name && cmd->exec_name[0])
		puterror(cmd, 3);
	return (1);
}
