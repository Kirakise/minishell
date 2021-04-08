#include "minishell.h"

t_shell	g_shell;

int main(int argc, char **argv, char **envp)
{
	char **line;
	char *s;

	init_struct();
	g_data.env = envcpy(envp);
	while (1) //позволил себе заменить true на 1, но можешь и bool подключить офк
	{
		write(g_shell.fd_1, "minishell>", 10);
		get_next_line(0, &s);
		line = get_commands(s);
		free(s);
	}
}


