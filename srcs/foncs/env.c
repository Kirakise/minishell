#include "../../includes/minishell.h"
#include "../../includes/libft.h"

extern t_shell g_shell;

void envprint(void)
{
	int i;

	i = 0;
	while (g_shell.env[i])
	{
		write(g_shell.fd_1, g_shell.env[i], ft_strlen(g_shell.env[i]));
		write(1, "\n", 1);
		i++;
	}
}
