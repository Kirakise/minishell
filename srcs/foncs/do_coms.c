#include "../../includes/minishell.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

extern t_shell	g_shell;

void	execute(t_cmd *cmd, int fd_in, int fd_out)
{
	dup2(fd_in, 0);
	dup2(fd_out, 1);
	if (!ft_strcmp("echo", cmd->exec_name))
		ft_echo(cmd);
	else if (!ft_strcmp("pwd", cmd->exec_name))
		pwd();
	else if (!ft_strcmp("env", cmd->exec_name))
		envprint(0);
	else if (!ft_strcmp("cd", cmd->exec_name) || !ft_strcmp("exit",
			cmd->exec_name) || !ft_strcmp("export", cmd->exec_name)
		|| !ft_strcmp("unset", cmd->exec_name))
		exit(0);
	else
		do_exec(cmd);
	exit(-1);
}

void	do_redirect(t_cmd *cmd, int *fd_out, int *fd_in)
{
	int	i;
	int	fd;

	i = 0;
	while (cmd->redir[i])
	{
		if (cmd->redir[i]->type == 0 || cmd->redir[i]->type == 1)
		{
			if (cmd->pipe && write(*fd_out, "\0", 1))
				close(*fd_out);
			if (cmd->redir[i]->type == 0)
				*fd_out = open(cmd->redir[i]->filename,
						O_WRONLY | O_CREAT | O_TRUNC, 0664);
			else if (cmd->redir[i]->type == 1)
				*fd_out = open(cmd->redir[i]->filename,
						O_WRONLY | O_CREAT | O_APPEND, 0664);
		}
		else
		{
			fd = open(cmd->redir[i]->filename, O_RDONLY);
			dup2(fd, *fd_in);
		}
		i++;
	}
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

void	normfunc(pid_t pid, pid_t pid2)
{
	int	status;

	status = g_shell.status;
	waitpid(pid, &g_shell.status, 0);
	waitpid(pid2, &g_shell.status, 0);
	if (WIFEXITED(g_shell.status))
		g_shell.status = WEXITSTATUS(g_shell.status);
	else if (WIFSIGNALED(g_shell.status) && WTERMSIG(g_shell.status) == 3
		&& write(1, "Quit: 3\n", 9))
		g_shell.status = 131;
	else if (WIFSIGNALED(g_shell.status))
		g_shell.status = WTERMSIG(g_shell.status) + 128;
	else
		wait(0);
	if (status != 0 && g_shell.status == 0)
		g_shell.status = status;
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
		subst_quotes_vars(cmd[i]);
		if (cmd[i]->redir)
			do_redirect(cmd[i], &fd_out, &fd_in);
		execute(cmd[i], fd_in, fd_out);
	}
	parentproc(cmd, i, fd_in, fd_out);
	normfunc(pid, pid2);
}
