#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

extern t_shell	g_shell;

void	restore_fd(void)
{
	dup2(g_shell.tmp_fd_0, 0);
	dup2(g_shell.tmp_fd_1, 1);
}

void	free_cmd(t_cmd **cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i]->args[j])
		{
			free(cmd[i]->args[j]);
			j++;
		}
		free(cmd[i]->args);
		free(cmd[i]->exec_name);
		i++;
		free(cmd[i - 1]);
	}
	free(cmd);
}

void	parentproc(t_cmd **cmd, int i)
{
	if (!ft_strcmp("cd", cmd[i]->exec_name))
		cd(cmd[i]);
	if (!ft_strcmp("exit", cmd[i]->exec_name))
		exit(0);
	restore_fd();
	free_cmd(cmd);
}