#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <fcntl.h>

extern t_shell g_shell;

void free_cmd(t_cmd **cmd)
{
	int i;
	int j;
	
	i = 0;
	while (cmd[i] && !(j = 0))
	{
		while(cmd[i]->args[j])
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

void do_coms(t_cmd **cmd)
{
	int i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i]->pipe && (g_shell.pipe0_open = 2))
			pipe(g_shell.fd);
		if (cmd[i]->redirect)
		{
			if (cmd[i]->redirect == 1)
				g_shell.fd_file = open(cmd[i + 1]->exec_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else
				g_shell.fd_file = open(cmd[i + 1]->exec_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
			dup2(g_shell.fd_file, 1);
		}
		g_shell.pidt = fork();
		if (!g_shell.pidt && cmd[i]->pipe)
		{
			dup2(g_shell.fd[1], 1);
			close(g_shell.fd[0]);
		}
		else if (g_shell.pidt && g_shell.pipe0_open == 2)
		{
			dup2(g_shell.fd[0], 0);
			close(g_shell.fd[1]);
			waitpid(g_shell.pidt, &g_shell.status, 0);
			dup2(1, g_shell.tmp_fd_1);
		}
		else if (g_shell.pidt)
			waitpid(g_shell.pidt, &g_shell.status, 0);
		if (!g_shell.pidt && !ft_strcmp("echo", cmd[i]->exec_name))
			echo(cmd[i]);
		else if (!g_shell.pidt &&!ft_strcmp("pwd", cmd[i]->exec_name))
			pwd();
		else if (!g_shell.pidt && !ft_strcmp("env", cmd[i]->exec_name))
			envprint();
		else if (!cmd[i]->pipe && !ft_strcmp("cd", cmd[i]->exec_name))
			cd(cmd[i]);
		else if (!ft_strcmp("exit", cmd[i]->exec_name))
			exit(0);
		else if (!g_shell.pidt)
			do_exec(cmd[i]);
		if (g_shell.pipe0_open-- == 1)
		{
			close(g_shell.fd[0]);
			dup2(g_shell.tmp_fd_0, 0);
		}
		if (g_shell.fd_file)
		{
			close(g_shell.fd_file);
			dup2(g_shell.tmp_fd_1, 1);
			i++;
		}
		i++;
	}
	free_cmd(cmd);
}