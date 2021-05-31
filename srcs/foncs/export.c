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
	if (!ret)
		malloc_err();
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

void	do_cycle(char *str)
{
	char	*s;
	char	*s2;

	if (!var_isvalid(str, 0))
	{
		ft_putstr("export: '");
		ft_putstr(str);
		ft_putstr_nl("': not a valid identifier");
		g_shell.status = 1;
		return ;
	}
	s = get_name(str);
	if (!s)
		return ;
	s2 = find_var(s);
	free(s);
	if (s2)
	{
		add_var_exist(str);
		free(s2);
	}
	else
		add_var(str);
}

void	export(t_cmd *cmd)
{
	int		i;

	i = 1;
	while (cmd->args[i])
	{
		do_cycle(cmd->args[i]);
		i++;
	}
	if (!cmd->args[1] && !fork())
		envprint(1);
	if (g_shell.status == 0)
		wait(&g_shell.status);
}
