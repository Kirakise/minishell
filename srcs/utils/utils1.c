#include "../../includes/minishell.h"

extern t_shell g_shell;

int	init_struct(void)
{
	g_shell.fd_1 = 1;
	g_shell.fd_0 = 0;
	g_shell.tmp_fd_1 = dup(g_shell.fd_1);
	g_shell.tmp_fd_0 = dup(g_shell.fd_0);
	return (1);
}

char	**envcpy(char **line)
{
	char	**res;
	int	i;

	i = 0;
	while (line[i])
		i++;
	if(!(res = malloc(sizeof(char *) * i)))
		return (0);
	res[i] = 0;
	i = 0;
	while (line[i])
		res[i] = ft_strdup(line[i]);
	return (res);
}
