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

static char	*parse_input(char **input, int *end, t_cmd *cmd)
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

static void	**lst_to_arr(t_list *lst, void **arr, int data_type)
{
	int		size;
	int		i;
	t_list	*lst_tmp;

	lst_tmp = lst;
	size = ft_lst_getsize(lst);
	arr = malloc(sizeof(t_list) * (size + 1));
	if (!arr)
		exit(1);//malloc
	i = 0;
	while (lst)
	{
		if (data_type == 0)
			arr[i] = (char *)lst->content;
		else
			arr[i] = (t_cmd *)lst->content;
		i++;
		lst = lst->next;
	}
	arr[i] = 0;
	ft_lstdestroy(&lst_tmp);
	return (arr);
}

static void	init_cmd_el(t_cmd *cmd, int *end)
{
	cmd->error = 0;
	cmd->pipe = 0;
	cmd->pipe_out = 0;
	cmd->redirect = 0;
	cmd->redir_in = 0;
	cmd->redir_out = 0;
	*end = 0;
}

static int	syntax_err(char *err)
{
	if (!err)
	{
		ft_putstr_nl("Syntax error");
		return (1);
	}
	ft_putstr("Syntax error near ");
	ft_putstr_nl(err);
	free(err);
	return (1);
}

int	str_to_commands(char *s, t_list **cmd_list)
{
	char	*str;
	char	*tmp;
	int		end;
	t_cmd	*cmd;
	t_list	*arg_list;

	while (*s)
	{
		arg_list = 0;
		cmd = malloc(sizeof(t_cmd));
		if (!cmd)
			exit(1);//malloc
		init_cmd_el(cmd, &end);
		str = parse_input(&s, &end, cmd);
		if (cmd->error)
			return (syntax_err(cmd->error));
		cmd->exec_name = ft_strdup(str);
		if (!cmd->exec_name)
			exit(1);//malloc
		free(str);
		str = ft_strdup(cmd->exec_name);
		if (!str)
			exit(1);//malloc
		ft_lstadd_back(&arg_list, ft_lstnew(str));
		while (*s && !end)
		{
			str = parse_input(&s, &end, cmd);
			if (cmd->error)
				return (syntax_err(cmd->error));
			if (end != 2)
			{
				tmp = ft_strdup(str);
				if (!tmp)
					exit(1);//malloc
				ft_lstadd_back(&arg_list, ft_lstnew(tmp));
			}
			free(str);
		}
		if (cmd->redirect)
		{
			end = 0;
			str = parse_input(&s, &end, cmd);
			if (cmd->error)
				return (syntax_err(cmd->error));
			cmd->redirect_filename = ft_strdup(str);
			if (!cmd->redirect_filename)
				exit (1);//malloc
			free(str);
		}
		while (ft_isspace(*s))
			s++;
		if (*s == '|')
		{
			cmd->pipe = 1;
			s++;
			if (*s == '|')
				cmd->error = ft_strdup("||");
		}
		cmd->args = (char **)lst_to_arr(arg_list, (void **)cmd->args, 0);
		ft_lstadd_back(cmd_list, ft_lstnew(cmd));
	}
	return (0);
}

t_cmd	**get_commands(char *s)
{
	t_list	*cmd_list;
	t_cmd	**cmd_arr;

	if (!s || !*s)
		return (0);
	cmd_list = 0;
	if (str_to_commands(s, &cmd_list) != 0)
		return (0);
	cmd_arr = 0;
	cmd_arr = (t_cmd **)lst_to_arr(cmd_list, (void **)cmd_arr, 1);
/*
	int i = 0;
	int j = 0;
	while (cmd_arr[i])
	{
		printf("\n%-6s %s\n", "cmd: ", cmd_arr[i]->exec_name);
		j = 0;
		while (cmd_arr[i]->args[j])
		{
			printf("arg[%d]: %s\n", j, cmd_arr[i]->args[j]);
			j++;
		}
		printf("pipe: %d\nredir: %d\n", cmd_arr[i]->pipe, cmd_arr[i]->redirect);
		if (cmd_arr[i]->redirect)
			printf("redir: %s\n", cmd_arr[i]->redirect_filename);
		i++;
	}
*/
	return (cmd_arr);
}
