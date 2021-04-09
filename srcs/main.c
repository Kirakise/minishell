#include "../includes/libft.h"
#include "../includes/minishell.h"

t_shell	g_shell;

int main(int argc, char **argv, char **envp)
{
	char	*s;
	t_cmd	**cmd;

	init_struct();
	cmd = 0;
	argc = argc;
	argv = argv;
	g_shell.env = envcpy(envp);
	while (1) //позволил себе заменить true на 1, но можешь и bool подключить офк
	{
		write(g_shell.fd_1, "minishell>", 10);
		get_next_line(0, &s);
		cmd = get_commands(s);
		free(s);
	}
}


