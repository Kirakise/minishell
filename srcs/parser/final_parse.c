#include "../../includes/minishell.h"

extern t_shell	g_shell;

static char	*handle_single_char(char **input, char c)
{
	if (c)
		*input += 1;
	if (c != '?')
		return (ft_strdup("$"));
	return (ft_itoa(g_shell.status));
}

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
		return (handle_single_char(input, s[i]));
	*input = s + i;
	name = ft_substr(s, 0, i);
	if (!name)
		malloc_err();
	value = find_var(name);
	free(name);
	if (!value)
		return (ft_strdup(""));
	return (value);
}

static char	*join(char *res, char *tmp)
{
	char	*tmp2;

	tmp2 = ft_strjoin(res, tmp);
	if (!tmp2)
		malloc_err();
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
	if (!res)
		malloc_err();
	ret = parse_str_chunk(&s, &tmp);
	while (ret)
	{
		res = join(res, tmp);
		tmp = get_var_value(&s);
		if (!tmp)
			malloc_err();
		res = join(res, tmp);
		ret = parse_str_chunk(&s, &tmp);
	}
	free(*str);
	*str = join(res, tmp);
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
