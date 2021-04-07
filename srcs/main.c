#include "minishell.h"

t_shell	g_shell;

int main(int argc, char **argv, char **envp)
{
	char **line;
	char *s;

	init_struct();
	g_data.env = envcpy(envp);
	while (true)
	{
		write(g_shell.fd_1, "minishell>", 10);
		get_next_line(0, &s);
		line = tvoipars(s);
	}
}


