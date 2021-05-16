#include "../includes/libft.h"
#include "../includes/minishell.h"

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
		write(g_shell.fd_1, "minishell> ", 11);
		setic(&term);
		s = tmpread();
		setc(&term);
		cmd = get_commands(s);
		history_update(&g_shell.hist, s);
		i = 0;
		if (cmd)
		{
			while(cmd[i])
				i++;
			do_coms(i - 1, cmd, dup(0), dup(1));
		}
	}
	history_free(&g_shell.hist);
}
