#include "../../includes/minishell.h"

extern t_shell	g_shell;

char	*get_name(char *s)
{
	char	*ret;
	int		i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != '=')
		i++;
	if (!s[i])
		return (0);
	ret = calloc(i + 1, 1);
	i = 0;
	while (s[i] && s[i] != '=')
	{
		ret[i] = s[i];
		i++;
	}
	return (ret);
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
		if (ft_strncmp(name, g_shell.env[i], ft_strlen(name)))
			ret[i] = g_shell.env[i];
		else
		{
			free(g_shell.env[i]);
			ret[i] = ft_strdup(s);
		}
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
	ret[i] = ft_strdup(s);
	i = 0;
	free(g_shell.env);
	g_shell.env = ret;
}

void	export(t_cmd *cmd)
{
	char	*s;
	char	*s2;
	int		i;

	i = 0;
	if (!cmd->args[1])
		envprint(1);
	else while (cmd->args[++i])
	{
		s = get_name(cmd->args[i]);
		if (s)
		{
			s2 = find_var(s);
			if (!s2)
				add_var(cmd->args[i]);
			else
				add_var_exist(cmd->args[i]);
			free(s);
			if (s2)
				free(s2);
		}
	}
}
