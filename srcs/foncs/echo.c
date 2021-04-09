#include "../../includes/minishell.h"
#include "../../includes/libft.h"

extern t_shell g_shell;

void	echo(char *s)
{
	write(g_shell.fd_1, s, ft_strlen(s));
}


