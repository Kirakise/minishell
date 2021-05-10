#include "../includes/libft.h"
#include "../includes/minishell.h"
#include <fcntl.h>

t_shell	g_shell;

int main(int argc, char **argv, char **envp)
{
	char	*s;
	t_cmd	**cmd;
	int 	i;
	struct termios term;

	init_struct();
	(void)argc;
	(void)argv;
	g_shell.env = envcpy(envp);
	if (setinit(&term))
		return (0);
	while (1)
	{
		i = 0;
		write(g_shell.fd_1, "minishell> ", 11);
		setic(&term);
		s = tmpread();
		setc(&term);
		cmd = get_commands(s);
		free(s);
		if (cmd [i])
		{
			while(cmd[i])
				i++;
			do_coms(i - 1, cmd, dup(0), dup(1));
		}
	}
}