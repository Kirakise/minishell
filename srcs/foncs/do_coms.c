#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

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

void execute(t_cmd *cmd, int fd_in, int fd_out)
{
		dup2(fd_in, 0);
		dup2(fd_out, 1);
		if (!ft_strcmp("echo", cmd->exec_name))
	        echo(cmd);
	    else if (!ft_strcmp("pwd", cmd->exec_name))
		    pwd();
	    else if (!ft_strcmp("env", cmd->exec_name))
		    envprint();
	    else if (!ft_strcmp("cd", cmd->exec_name))
		    cd(cmd);
	    else if (!ft_strcmp("exit", cmd->exec_name))
		    exit(0);
		else
			do_exec(cmd);
		exit(-1);
}

void restore_fd()
{
	dup2(g_shell.tmp_fd_0, 0);
	dup2(g_shell.tmp_fd_1, 1);
}

void do_coms(int i, t_cmd **cmd, int fd_in, int fd_out)
{
	pid_t pid;
	pid_t pid2;
	int fd[2];

	pid = 0;
	pid2 = 0;
	if (i > 0)
	{
		if (cmd[i - 1]->pipe)
		{
			pipe(fd);
			fd_in = fd[0];
			if (!(pid = fork()))
			{
				close(fd[0]);
				do_coms(i - 1, cmd, dup(g_shell.tmp_fd_0), fd[1]);
				exit(0);
			}
			close(fd[1]);
		}
	}
	if(!(pid2 = fork()))
		execute(cmd[i], fd_in, fd_out);
	waitpid(pid2, &g_shell.status, 0);
	if (pid)
		waitpid(pid, &g_shell.status, WNOHANG);
	if (g_shell.pidt == i)
	{
		restore_fd();
		free_cmd(cmd);
	}
}
