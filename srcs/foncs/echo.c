#include "minishell.h"

extern g_shell;

void	echo(char *s)
{
	write(g_shell.fd_1, s, ft_strlen(s));
}


