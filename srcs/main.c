#include "../includes/libft.h"
#include "../includes/minishell.h"
#include <fcntl.h>

t_shell	g_shell;

int main(int argc, char **argv, char **envp)
{
	char	*s;
	t_cmd	**cmd;
	int 	i;
	char	*term_name;
	struct termios term;

	init_struct();
	(void)argc;
	(void)argv;
	g_shell.env = envcpy(envp);
	term_name = "xterm-256color";
	tcgetattr(0, &term);
	term.c_lflag &= !(ECHO);
	term.c_lflag &= !(ICANON);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tgetent(0, term_name);
	tcsetattr(0, TCSANOW, &term);
	while (1)
	{
		i = 0;
		write(g_shell.fd_1, "minishell> ", 11);
		s = tmpread();
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


