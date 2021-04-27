#include "../includes/libft.h"
#include "../includes/minishell.h"
#include <fcntl.h>

t_shell	g_shell;

int main(int argc, char **argv, char **envp)
{
	char	*s;
	t_cmd	**cmd;
	int 	i;

	init_struct();
	(void)argc;
	(void)argv;
	g_shell.env = envcpy(envp);
	while (1)
	{
		i = 0;
		write(g_shell.fd_1, "minishell> ", 11);
		get_next_line(0, &s);
		cmd = get_commands(s);
		free(s);
		if (cmd [i])
		{
			while(cmd[i])
				i++;
			g_shell.pidt = i - 1;	
			do_coms(i - 1, cmd, dup(0), dup(1));
		}
	}
}


