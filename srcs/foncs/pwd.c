#include "../../includes/minishell.h"
#include "../../includes/libft.h"

extern t_shell g_shell;

void	pwd(void)
{
	char *s;

	s = malloc(256);
	getcwd(s, 255);
	if (s)
		write(g_shell.fd_1, s, ft_strlen(s));
}
