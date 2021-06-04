#include "../../includes/minishell.h"
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

extern t_shell	g_shell;

void	checkinp(t_cmd *cmd)
{
	int			i;
	char		*s;
	struct stat	tmp;

	if (ft_strchr('/', cmd->exec_name))
	{
		if (cmd->exec_name[0] == '/')
			i = stat(cmd->exec_name, &tmp);
		else
			i = stat(ft_strjoin_3(find_var("PWD"), "/", cmd->exec_name), &tmp);
		if (i == -1)
		{
			s = strerror(errno);
			ft_putstr_nl(s);
			exit(127);
		}
		if (S_ISDIR(tmp.st_mode))
		{
			ft_putstr("minishell: ");
			ft_putstr(cmd->exec_name);
			ft_putstr_nl(" is a directory");
			exit(126);
		}
		else if ((tmp.st_mode & S_IXUSR) == 0)
		{
			ft_putstr("minishell: ");
			ft_putstr(cmd->exec_name);
			ft_putstr_nl(" Permission denied");
			exit(126);
		}
	}
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
	{
		ft_putstr("minishell: command not found: ");
		ft_putstr_nl(cmd->exec_name);
		exit(127);
	}
	return (1);
}