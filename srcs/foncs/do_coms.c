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

void do_coms(int i, t_cmd **cmd, int fd_in, int fd_out)
{
    pid_t pid;
    int fd[2];

    pid = fork();
    if (!pid)
    {
        dup2(fd_in, 0);
        dup2(fd_out, 1);
        if (cmd[i + 1])
        {
            if (cmd[i]->pipe)
            {
                pipe(fd);
                dup2(fd[1], 1);
                do_coms(i + 1, cmd, fd[0], dup(g_shell.tmp_fd_1));
            }
        }
        if (!ft_strcmp("echo", cmd[i]->exec_name))
	        echo(cmd[i]);
	    else if (!ft_strcmp("pwd", cmd[i]->exec_name))
		    pwd();
	    else if (!ft_strcmp("env", cmd[i]->exec_name))
		    envprint();
	    else if (!ft_strcmp("cd", cmd[i]->exec_name))
		    cd(cmd[i]);
	    else if (!ft_strcmp("exit", cmd[i]->exec_name))
		    exit(0);
	    else
		    do_exec(cmd[i]);
    }
    else if (i == 0 && pid)
    {
        waitpid(pid, &g_shell.status, 0);
        dup2(g_shell.tmp_fd_0, 0);
        dup2(g_shell.tmp_fd_1, 1);
    }
}
