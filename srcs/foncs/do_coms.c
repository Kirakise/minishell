#include "../../includes/minishell.h"
#include "../../includes/libft.h"

extern t_shell g_shell;

void do_coms(t_cmd **cmd)
{
	int i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i]->pipe && (g_shell.pipe0_open = 2))
			pipe(g_shell.fd);
		g_shell.pidt = fork();
		if (!g_shell.pidt)
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
		else if (!ft_strcmp("exit", cmd[i]->exec_name))
			exit(0);
		else if (!g_shell.pidt)
			do_exec(cmd[i]);
		if (g_shell.pipe0_open-- == 1)
		{
			close(g_shell.fd[0]);
			dup2(g_shell.tmp_fd_0, 0);
		}
		i++;
	}
}