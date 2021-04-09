#include <stdio.h>
#include "../../includes/minishell.h"
#include "../../includes/libft.h"

//  вот эту функцию можно применить в той части программы, которая выполняет команды,
//  заменив return на вызов соответствующих функций

static int get_typeof_cmd(char *str)
{
	if (!ft_strcmp(str, "echo"))
		return (c_echo);
	else if (!ft_strcmp(str, "cd"))
		return (c_cd);
	else if (!ft_strcmp(str, "pwd"))
		return (c_pwd);
	else if (!ft_strcmp(str, "export"))
		return (c_export);
	else if (!ft_strcmp(str, "unset"))
		return (c_unset);
	else if (!ft_strcmp(str, "env"))
		return (c_env);
	else if (!ft_strcmp(str, "exit"))
		return (c_exit);
	return (c_exec);
}

static void handle_quotes(int *val)
{
	int quotes;

	quotes = *val;
	if (quotes == 0)
		quotes++;
	else
		quotes--;
	*val = quotes;
}

static char *parse_input(char **input, int *end)
{
	int		quotes[2];
	char	*s;
	char	*str;
	int		i;

	s = *input;
	while (ft_isspace(*s))
		s++;
	str = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!str)
		exit(1); // malloc protection....
	i = 0;
	quotes[0] = 0;
	quotes[1] = 0;
	while (*s && !*end && (!ft_isspace(*s) || quotes[0] || quotes[1]))
	{
		if (*s == '\'')
			handle_quotes(&quotes[0]);
		else if (*s == '"')
			handle_quotes(&quotes[1]);
		else if (*s == ';' && !quotes[0] && !quotes[1])
			*end = 1;
		else
		{
			str[i] = *s;
			i++;
		}
		s++;
	}
	str[i] = 0;
	*input = s;
	return (str);
}

static void	**lst_to_arr(t_list *lst, void **arr, int data_type)
{
	int		size;
	int		i;
	t_list	*lst_tmp;

	lst_tmp = lst;
	size = ft_lst_getsize(lst);
	arr = malloc(sizeof(t_list) * size + 1);
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

t_cmd	**get_commands(char *s)
{
	char	*str;
	int		end;
	t_cmd	*cmd;
	t_list	*lst;
	t_list	*arg_list;

//	printf("\n%-8s%s\n", "in: ", s);//
	lst = 0;
	while (*s)
	{
		arg_list = 0;
		cmd = malloc(sizeof(t_cmd));
		cmd->pipe = 0;
		cmd->pipe_out = 0;
		end = 0;
		str = parse_input(&s, &end);
		cmd->type = get_typeof_cmd(str);
		cmd->exec_name = ft_strdup(str);
		if (!cmd->exec_name)
			exit(1);//malloc
		ft_lstadd_back(&arg_list, ft_lstnew(str));
		str = 0;
		while (*s && !end)
		{
			str = parse_input(&s, &end);
			if (ft_strcmp(str, "|") != 0)
				ft_lstadd_back(&arg_list, ft_lstnew(str));
			else
			{
				cmd->pipe = 1;
				end = 1;
			}
			str = 0;
		}
		cmd->args = (char **)lst_to_arr(arg_list, (void **)cmd->args, 0);
		ft_lstadd_back(&lst, ft_lstnew(cmd));
	}

	t_cmd	**cmd_arr;

	cmd_arr = 0;
	cmd_arr = (t_cmd **)lst_to_arr(lst, (void **)cmd_arr, 1);

/*
	int i = 0;
	int j = 0;
	while (cmd_arr[i])
	{
		printf("%-6s%d %s\n", "cmd: ", cmd_arr[i]->type, cmd_arr[i]->exec_name);
		j = 0;
		while (cmd_arr[i]->args[j])
		{
			printf("arg[%d]: %s\n", j, cmd_arr[i]->args[j]);
			j++;
		}
		printf("pipe: %d\n", cmd_arr[i]->pipe);
		i++;
	}
*/
	return (cmd_arr);
}
