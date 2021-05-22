#include "../../includes/minishell.h"

extern t_shell	g_shell;

static char	*get_var_value(char **input)
{
	int		i;
	char	*s;
	char	*name;
	char	*value;

	s = *input;
	i = 0;
	while (ft_isalnum(s[i]))
		i++;
	if (i == 0)
	{
		if (s[i])
			*input += 1;
		if (s[i] != '?')
			return (ft_strdup("$"));
		return (ft_itoa(g_shell.status));
	}
	*input = s + i;
	name = ft_substr(s, 0, i);//malloc
	if (!name)
		return (0);
	value = find_var(name);//malloc
	free(name);
	return (value);
}

static char	*join(char *res, char *tmp)
{
	char	*tmp2;

	tmp2 = ft_strjoin(res, tmp);//malloc
	free(res);
	free(tmp);
	return (tmp2);
}

static void	final_parse(char **str)
{
	char	*s;
	char	*res;
	char	*tmp;
	int		ret;

	if (!str || !*str)
		return ;
	s = *str;
	res = ft_strdup("");
	ret = parse_str_chunk(&s, &tmp);//malloc
	while (ret)
	{
		res = join(res, tmp);//malloc
		tmp = get_var_value(&s);//malloc
		res = join(res, tmp);//malloc
		ret = parse_str_chunk(&s, &tmp);//malloc
	}
	if (ret == 0)
		*str = join(res, tmp);//malloc
}

void	subst_quotes_vars(t_cmd *cmd)
{
	int	i;

	final_parse(&cmd->exec_name);
	i = 0;
	while (cmd->args[i])
		final_parse(&cmd->args[i++]);
	i = 0;
	while (cmd->redir && cmd->redir[i])
		final_parse(&cmd->redir[i++]->filename);
}
