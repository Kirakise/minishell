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

// static int	is_a_builtin(char *exec_name)
// {
// 	if (!ft_strcmp(exec_name, "export")
// 		|| !ft_strcmp(exec_name, "exit")
// 		|| !ft_strcmp(exec_name, "pwd")
// 		|| !ft_strcmp(exec_name, "cd")
// 		|| !ft_strcmp(exec_name, "unset")
// 		|| !ft_strcmp(exec_name, "env"))
// 		return (1);
// 	return (0);
// }

void	set_status(t_cmd *cmd, pid_t pid, pid_t pid2)
{
	int	status;

	status = g_shell.status;
	if (pid)
		waitpid(pid, &g_shell.status, 0);
	if (pid2)
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
	if (!g_shell.status && status && !ft_strcmp("export", cmd->exec_name))
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
	subst_quotes_vars(cmd[i]);
	pid2 = fork();
	if (!pid2)
	{
		if (cmd[i]->redir)
			do_redirect(cmd[i], &fd_out, &fd_in);
		execute(cmd[i], fd_in, fd_out);
	}
	parentproc(cmd, i, fd_in, fd_out);
	set_status(cmd[i], pid, pid2);
}
