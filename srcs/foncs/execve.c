#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <string.h>
#include <unistd.h>

extern t_shell	g_shell;

int	do_exec(t_cmd *cmd)
{
	char	*s;
	int		i;
	char	**dirs;

	i = 0;
	s = find_var("PATH");
	dirs = ft_split(s, ':');
	while (dirs[i])
	{
		s = ft_strjoin(dirs[i], "/");
		s = ft_strjoin(s, cmd->exec_name);
		execve(s, cmd->args, g_shell.env);
		i++;
	}
	execve(cmd->exec_name, cmd->args, g_shell.env);
	dup2(g_shell.tmp_fd_1, 1);
	ft_putstr("minishell: command not found: ");
	ft_putstr_nl(cmd->exec_name);
	exit(-1);
	return (1);
}
