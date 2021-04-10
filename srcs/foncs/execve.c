#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <string.h>
#include <unistd.h>

extern t_shell g_shell;

int do_exec(t_cmd *cmd)
{
	char *s;
	char *s2;

	s = ft_strjoin("/bin/", cmd->exec_name);
	s2 = ft_strjoin("/usr/bin/", cmd->exec_name);
	if (open(cmd->exec_name, O_RDONLY) != -1)
		execve(cmd->exec_name, cmd->args, g_shell.env);
	if (open(s, O_RDONLY) != -1)
		execve(s, cmd->args, g_shell.env);
	execve(s2, cmd->args, g_shell.env);
	char *s1 = strerror(errno);
	printf("%s\n", s1);
	exit(-1);
	return (1);
}