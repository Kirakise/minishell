#include "../../includes/minishell.h"

extern t_shell	g_shell;

static void	check_var_end(char **str)
{
	char	*s;
	char	*tmp;

	s = *str;
	while (*s && *s != '=')
		s++;
	if (!*s)
	{
		tmp = ft_strjoin(*str, "=");
		if (!tmp)
			malloc_err();
		free(*str);
		*str = tmp;
	}
}

static char	*new_var(char *s)
{
	char	*res;
	int		i;

	i = 0;
	while (s[i] && s[i] != '+')
		i++;
	if (s[i] == '+')
	{
		s[i] = 0;
		res = ft_strjoin(s, s + i + 1);
		s[i] = '+';
	}
	else
		res = ft_strdup(s);
	if (!res)
		malloc_err();
	return (res);
}

char	*update_var(char *orig, char *new)
{
	char	*res;
	int		i;

	i = 0;
	while (new[i] && new[i] != '+' && new[i] != '=')
		i++;
	if (new[i] == '+')
	{
		check_var_end(&orig);
		res = ft_strjoin(orig, new + i + 2);
	}
	else
		res = ft_strdup(new);
	if (!res)
		malloc_err();
	free(orig);
	return (res);
}

void	add_var_exist(char *s)
{
	int		i;
	char	**ret;
	char	*name;

	name = get_name(s);
	i = 0;
	while (g_shell.env[i])
		i++;
	ret = calloc(i + 1, sizeof(char *));
	i = 0;
	while (g_shell.env[i])
	{
		if (!ft_strncmp(name, g_shell.env[i], ft_strlen(name)))
			ret[i] = update_var(g_shell.env[i], s);
		else
			ret[i] = g_shell.env[i];
		i++;
	}
	free(name);
	free(g_shell.env);
	g_shell.env = ret;
}

void	add_var(char *s)
{
	int		i;
	char	**ret;

	i = 0;
	while (g_shell.env[i])
		i++;
	ret = calloc(i + 2, sizeof(char *));
	i = 0;
	while (g_shell.env[i])
	{
		ret[i] = g_shell.env[i];
		i++;
	}
	ret[i] = new_var(s);
	free(g_shell.env);
	g_shell.env = ret;
}
