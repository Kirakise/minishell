#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <string.h>
#include <unistd.h>

extern t_shell g_shell;

int do_exec(t_cmd *cmd)
{
	execve(cmd->exec_name, cmd->args, g_shell.env);
	char *s1 = strerror(errno);
	printf("%s\n", s1);
	exit(-1);
	return (1);
}