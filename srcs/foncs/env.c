#include "../../includes/minishell.h"

extern t_shell	g_shell;

static char	**copy_env(char **arr)
{
	char	**res;
	int		size;
	int		i;

	size = 0;
	while (arr[size])
		size++;
	res = malloc(sizeof(char *) * (size + 1));
	if (!res)
		malloc_err();
	i = 0;
	while (i < size)
	{
		res[i] = arr[i];
		i++;
	}
	res[i] = 0;
	return (res);
}

static char	**sort_alpha(char **arr)
{
	char	**res;
	char	*swap;
	int		i;
	int		j;

	res = copy_env(arr);
	i = 0;
	while (res[i])
	{
		j = 1;
		while (res[i + j])
		{
			if (ft_strcmp(res[i], res[i + j]) > 0)
			{
				swap = res[i];
				res[i] = res[i + j];
				res[i + j] = swap;
			}
			j++;
		}
		i++;
	}
	return (res);
}

static void	print_var(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	write(g_shell.fd_1, str, i + 1);
	write(g_shell.fd_1, "\"", 1);
	str += i + 1;
	write(g_shell.fd_1, str, ft_strlen(str));
	write(g_shell.fd_1, "\"\n", 2);
}

void	envprint(int regime)
{
	int		i;
	char	**env;

	i = 0;
	env = sort_alpha(g_shell.env);
	while (env[i])
	{
		if (regime)
			write(g_shell.fd_1, "declare -x ", 11);
		print_var(env[i]);
		i++;
	}
	free(env);
	exit(0);
}
