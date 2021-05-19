#include "../../includes/minishell.h"

static void	handle_quotes(int *val)
{
	int	quotes;

	quotes = *val;
	if (quotes == 0)
		quotes++;
	else
		quotes--;
	*val = quotes;
}

static void	handle_end_chars(char **s, t_cmd *cmd, int *end, int i)
{
	char	*str;

	str = *s;
	if (*str == ';')
	{
		str++;
		if (*str == ';')
			cmd->error = ft_strdup(";;");
	}
	else if (*str == '|')
	{
		cmd->pipe = 1;
		str++;
		if (*str == '|')
			cmd->error = ft_strdup("||");
	}
	else if (!ft_strncmp(str, ">>", 2))
	{
		cmd->redirect = 2;
		str += 2;
		if (*str == '>')
			cmd->error = ft_strdup(">>>");
	}
	else if (*str == '>')
	{
		cmd->redirect = 1;
		str++;
	}
	if (i == 0)
		*end = 2;
	else
		*end = 1;
	*s = str - 1;
}

static char *check_close_quotes(int single, int dbl)
{
	if (single)
		return (ft_strdup("\'"));
	if (dbl)
		return (ft_strdup("\""));
	return (0);
}

static char	*str_iter(char *s, int *end, t_cmd *cmd, char *str)
{
	int	i;
	int	quotes[2];

	i = 0;
	quotes[0] = 0;
	quotes[1] = 0;
	while (*s && !*end && (!ft_isspace(*s) || quotes[0] || quotes[1]))
	{
		if (!quotes[1] && *s == '\'')
			handle_quotes(&quotes[0]);
		else if (!quotes[0] && *s == '"')
			handle_quotes(&quotes[1]);
		else if (!quotes[0] && !quotes[1] && ft_strchr(*s, ";|>"))
			handle_end_chars(&s, cmd, end, i);
		else
			str[i++] = *s;
		s++;
	}
	str[i] = 0;
	cmd->error = check_close_quotes(quotes[0], quotes[1]);
	return (s);
}

char	*parse_input(char **input, int *end, t_cmd *cmd)
{
	char	*s;
	char	*str;

	s = *input;
	while (ft_isspace(*s))
		s++;
	str = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!str)
		exit(1); // malloc protection....
	*input = str_iter(s, end, cmd, str);
	subst_vars(&str);
	return (str);
}
