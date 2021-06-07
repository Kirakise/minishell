#include "../../includes/minishell.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

extern t_shell	g_shell;

static void	restore_fd(void)
{
	dup2(g_shell.tmp_fd_0, 0);
	dup2(g_shell.tmp_fd_1, 1);
}

static void	free_cmd_el(t_cmd *cmd)
{
	int	j;

	j = 0;
	while (cmd->args[j])
	{
		free(cmd->args[j]);
		j++;
	}
	free(cmd->args);
	free(cmd->exec_name);
	free(cmd->error);
	if (cmd->redir)
	{
		j = 0;
		while (cmd->redir[j])
		{
			free(cmd->redir[j]->filename);
			free(cmd->redir[j]);
			j++;
		}
		free(cmd->redir);
	}
	free(cmd);
}

void	free_cmd(t_cmd **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		free_cmd_el(cmd[i]);
		i++;
	}
	free(cmd);
}

void	parentproc(t_cmd **cmd, int i, int fd_in, int fd_out)
{
	int	tmp;

	close(fd_in);
	close(fd_out);
	if (!ft_strcmp("cd", cmd[i]->exec_name))
	{
		if (i > 0 && cmd[i - 1]->pipe)
		{
			tmp = fork();
			if (!tmp)
			{
				cd(cmd[i]);
				exit(g_shell.status);
			}
		}
		else
			cd(cmd[i]);
	}
	else if (!ft_strcmp("exit", cmd[i]->exec_name))
		sh_exit(cmd, i);
	else if (!ft_strcmp("export", cmd[i]->exec_name))
		export(cmd[i]);
	else if (!ft_strcmp("unset", cmd[i]->exec_name))
		unset(cmd[i]);
	restore_fd();
}
