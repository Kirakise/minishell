#include "../../includes/minishell.h"
#include "../../includes/libft.h"

extern t_shell g_shell;

void do_pipes(t_cmd *cmd) //Pipe чет сложный, но должен работать
{
	pipe(g_shell.fd);
	if (cmd->pipe && cmd->pipe_out && cmd->args[1] == 0)
	{
		dup2(g_shell.fd[1], g_shell.fd_1);
		dup2(g_shell.fd[0], g_shell.fd_0);
	}
	else if (cmd->pipe)
	{
		dup2(g_shell.fd[1], g_shell.fd_1);
		close(g_shell.fd[0]);
	}
	else if (cmd->pipe_out && cmd->args[1] == 0)
	{
		dup2(g_shell.fd[0], g_shell.fd_0);
		close(g_shell.fd[1]);
	}
}

void restore_fd() //После работы с пайпом
{
	g_shell.fd_1 = dup(g_shell.tmp_fd_1);
	g_shell.fd_0 = dup(g_shell.tmp_fd_0);
	close(g_shell.fd[0]);
	close(g_shell.fd[1]);
}

void do_coms(t_cmd **cmd)
{
	int i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i]->pipe)
			do_pipes(cmd[i]);
		if (!ft_strcmp("echo", cmd[i]->exec_name))
			echo(cmd[i]->args);
		else if (!ft_strcmp("pwd", cmd[i]->exec_name))
			pwd();
		else if (!ft_strcmp("env", cmd[i]->exec_name))
			envprint();
		else
			do_exec(cmd[i]);
		i++;
		restore_fd();
	}
}