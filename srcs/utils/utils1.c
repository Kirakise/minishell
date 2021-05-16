#include "../../includes/minishell.h"

extern t_shell	g_shell;

int	init_struct(void)
{
	g_shell.fd_1 = STDOUT_FILENO;
	g_shell.fd_0 = STDIN_FILENO;
	g_shell.tmp_fd_1 = dup(g_shell.fd_1);
	g_shell.tmp_fd_0 = dup(g_shell.fd_0);
	g_shell.pidt = -1;
	g_shell.hist = 0;
	return (1);
}

char	*find_var(char *s1)
{
	int		i;
	int		j;
	char	*ret;
	int		size;

	i = 0;
	j = 0;
	while (g_shell.env[i])
	{
		if (!ft_strncmp(s1, g_shell.env[i], ft_strlen(s1))
			&& g_shell.env[i][ft_strlen(s1)] == '=')
		{
			size = ft_strlen(g_shell.env[i]) - ft_strlen(s1) - 1;
			ret = ft_strdup(g_shell.env[i] + ft_strlen(s1) + j + 1);
			return (ret);
		}
		i++;
	}
	return (ft_strdup(""));
}

char	**envcpy(char **line)
{
	char	**res;
	int		i;

	i = 0;
	while (line[i])
		i++;
	res = malloc(sizeof(char *) * (i + 1));
	if (!res)
		return (0);
	res[i] = 0;
	i = 0;
	while (line[i])
	{
		res[i] = ft_strdup(line[i]);
		i++;
	}
	return (res);
}
