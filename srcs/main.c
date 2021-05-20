#include "../includes/minishell.h"

t_shell	g_shell;

/*static void	exec_commands(t_cmd **cmd)
{
	int	i;

	if (!cmd)
		return ;
	i = 0;
	while (cmd[i])
		i++;
	do_coms(i - 1, cmd, dup(0), dup(1));
	free_cmd(cmd);
}*/

int	main(int argc, char **argv, char **envp)
{
	char			*s;
	t_cmd			**cmd;
	struct termios	term;

	init_struct(argc, argv);
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
		//exec_commands(cmd);
	}
	history_free(&g_shell.hist);
}
