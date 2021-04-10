#include "../includes/libft.h"
#include "../includes/minishell.h"
#include <fcntl.h>

t_shell	g_shell;

int main(int argc, char **argv, char **envp)
{
	char	*s;
	t_cmd	**cmd;

	init_struct();
	(void)argc;
	(void)argv;
	g_shell.env = envp;
	while (1)
	{
		write(g_shell.fd_1, "minishell> ", 11);
		get_next_line(0, &s);
		cmd = get_commands(s);
		free(s);
		do_coms(cmd);
	}
}


