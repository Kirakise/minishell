#include "../includes/minishell.h"

t_shell	g_shell;

static void	exec_commands(t_cmd **cmd)
{
	int	i;

	if (!cmd)
		return ;
	i = 0;
	while (cmd[i])
		i++;
	do_coms(i - 1, cmd, dup(0), dup(1));
	free_cmd(cmd);
}

/*static void	test_print(t_cmd **cmd_arr)
{
	int	i;
	int	j;

	i = 0;
	while (cmd_arr[i])
	{
		printf("\n%-6s %s|\n", "cmd   :   ", cmd_arr[i]->exec_name);
		j = 0;
		while (cmd_arr[i]->args[j])
		{
			printf("arg[%d]:    %s|\n", j, cmd_arr[i]->args[j]);
			j++;
		}
		printf("pipe  :    %d\n", cmd_arr[i]->pipe);
		j = 0;
		while (cmd_arr[i]->redir && cmd_arr[i]->redir[j])
		{
			printf("redir : ");
			if (cmd_arr[i]->redir[j]->type == 0)
				printf(" > ");
			else if (cmd_arr[i]->redir[j]->type == 1)
				printf(">> ");
			else
				printf(" < ");
			printf("%s|\n", cmd_arr[i]->redir[j]->filename);
			j++;
		}
		i++;
	}
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
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		write(g_shell.fd_1, "minishell> ", 11);
		setic(&term);
		s = tmpread();
		setc(&term);
		cmd = get_commands(s);
	//	test_print(cmd);
		history_update(&g_shell.hist, s);
		exec_commands(cmd);
	}
	history_free(&g_shell.hist);
}
