#include "../../includes/minishell.h"

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
	cmd->exec_name = 0;
	cmd->redirect_filename = 0;
	cmd->args = 0;
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

static int parse_command(char **s, t_cmd *cmd, int *end, t_list **arg_list)
{
	char	*str;

	str = parse_input(s, end, cmd);//malloc
	if (cmd->error)
		return (syntax_err(cmd->error));//return err
	cmd->exec_name = ft_strdup(str);//malloc
	free(str);
	str = ft_strdup(cmd->exec_name);//malloc
	ft_lstadd_back(arg_list, ft_lstnew(str));
	return (0);
}

static int	parse_arguments(char **s, t_cmd *cmd, int *end, t_list **arg_list)
{
	char	*str;
	char	*tmp;

	while (**s && !*end)
	{
		str = parse_input(s, end, cmd);//malloc
		if (cmd->error)
			return (syntax_err(cmd->error));
		if (*end != 2)
		{
			tmp = ft_strdup(str);//malloc
			ft_lstadd_back(arg_list, ft_lstnew(tmp));
		}
		free(str);
	}
	return (0);
}

int	str_to_commands(char *s, t_list **cmd_list)
{
	char	*str;
	int		end;
	t_cmd	*cmd;
	t_list	*arg_list;

	while (*s)
	{
		arg_list = 0;
		cmd = malloc(sizeof(t_cmd));//malloc
		init_cmd_el(cmd, &end);
		parse_command(&s, cmd, &end, &arg_list);
		parse_arguments(&s, cmd, &end, &arg_list);
		if (cmd->redirect)
		{
			end = 0;
			str = parse_input(&s, &end, cmd);//malloc
			if (cmd->error)
				return (syntax_err(cmd->error));
			cmd->redirect_filename = ft_strdup(str);//malloc
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
