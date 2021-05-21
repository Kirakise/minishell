#include "../../includes/minishell.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

extern t_shell	g_shell;

/*void	execute(t_cmd *cmd, int fd_in, int fd_out)
{
	subst_quotes_vars(cmd);
	dup2(fd_in, 0);
	dup2(fd_out, 1);
	if (!ft_strcmp("echo", cmd->exec_name))
		ft_echo(cmd);
	else if (!ft_strcmp("pwd", cmd->exec_name))
		pwd();
	else if (!ft_strcmp("env", cmd->exec_name))
		envprint();
	else if (!ft_strcmp("cd", cmd->exec_name) || !ft_strcmp("exit",
			cmd->exec_name) || !ft_strcmp("export", cmd->exec_name)
		|| !ft_strcmp("unset", cmd->exec_name))
		exit(0);
	else
		do_exec(cmd);
	exit(-1);
}

void	do_redirect(t_cmd *cmd, int *fd_out)
{
	if (cmd->pipe)
	{
		write(*fd_out, 0, 1);
		close(*fd_out);
	}
	if (cmd->redirect == 1)
		*fd_out = open(cmd->redirect_filename,
				O_WRONLY | O_CREAT | O_TRUNC, 0664);
	else if (cmd->redirect == 2)
		*fd_out = open(cmd->redirect_filename,
				O_WRONLY | O_CREAT | O_APPEND, 0664);
	free(cmd->redirect_filename);
}

void	do_pipe(int i, t_cmd **cmd, int *fd_in, pid_t *pid)
{
	int	fd[2];

	pipe(fd);
	*fd_in = fd[0];
	*pid = fork();
	if (!(*pid))
	{
		close(fd[0]);
		do_coms(i - 1, cmd, dup(g_shell.tmp_fd_0), fd[1]);
		exit(0);
	}
	close(fd[1]);
}

void	do_coms(int i, t_cmd **cmd, int fd_in, int fd_out)
{
	pid_t	pid;
	pid_t	pid2;

	pid = 0;
	pid2 = 0;
	if (i > 0)
	{
		if (cmd[i - 1]->pipe)
			do_pipe(i, cmd, &fd_in, &pid);
		else
			do_coms(i - 1, cmd, dup(g_shell.tmp_fd_0), dup(g_shell.tmp_fd_1));
	}
	pid2 = fork();
	if (!pid2)
	{
		if (cmd[i]->redirect)
			do_redirect(cmd[i], &fd_out);
		execute(cmd[i], fd_in, fd_out);
	}
	parentproc(cmd, i, fd_in, fd_out);
	waitpid(pid, &g_shell.status, 0);
	waitpid(pid2, &g_shell.status, 0);
}
*/
