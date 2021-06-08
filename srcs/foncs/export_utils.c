#include "../../includes/minishell.h"

extern t_shell	g_shell;

int	export_puterr(char *str)
{
	ft_putstr("export: '");
	ft_putstr(str);
	ft_putstr_nl("': not a valid identifier");
	g_shell.status = 1;
	return (0);
}

char	*get_name(char *s)
{
	char	*ret;
	int		i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != '+' && s[i] != '=')
		i++;
	ret = calloc(i + 1, 1);
	if (!ret)
		malloc_err();
	i = 0;
	while (s[i] && s[i] != '+' && s[i] != '=')
	{
		ret[i] = s[i];
		i++;
	}
	return (ret);
}
