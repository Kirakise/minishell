#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <string.h>
#include <unistd.h>

extern t_shell g_shell;

int do_exec(t_cmd *cmd)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		char **s = g_shell.env;
		execve(cmd->exec_name, s, g_shell.env);
		char *s1 = strerror(errno);
		printf("%s\n", s1);
	}
	return (1);
}