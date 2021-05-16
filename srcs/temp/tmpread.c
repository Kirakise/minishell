#include "../../includes/minishell.h"
#include "../../includes/libft.h"
extern t_shell g_shell;

int ft_putchar(int s)
{
	return (write(g_shell.fd_1, &s, 1));
}
int ft_putint(int a)
{
	return (write(g_shell.fd_1, &a, 4));
}

int delete_last(char *s)
{
	int i;

	i = 0;
	if (!s || !s[i])
		return (-1);
	while (s[i])
		i++;
	s[i - 1] = 0;
	return (1);
}

static void access_history(char *str, char **s, int *end)
{
	tputs(restore_cursor, g_shell.tmp_fd_1, ft_putchar);
	tputs(tigetstr("ed"), 1, ft_putchar);
	free(*s);
	if (!ft_strcmp(str, "\e[A"))
		*s = get_history_line(&g_shell.hist, 1, end);
	else
		*s = get_history_line(&g_shell.hist, -1, end);
	if (*s)
		ft_putstr(*s);
		//write(g_shell.tmp_fd_1, s, ft_strlen(s));
}

char *tmpread()
{
	int l;
	int end;
	char *str;
	char *s;
	char *tmp;

	s = ft_calloc(1, 1);
	str = ft_calloc(1, 1);
	end = 0;
	tputs(save_cursor, 1, ft_putchar);
	while (ft_strcmp(str, "\n"))
	{
		free(str);
		str = ft_calloc(5, 1);
		l = read(g_shell.tmp_fd_0, str, 10);
		if (!ft_strcmp(str, "\e[A") || !ft_strcmp(str, "\e[B"))
			access_history(str, &s, &end);
		else if (!ft_strcmp(str, "\e[C") || !ft_strcmp(str, "\e[D"))
			tmp = 0;
		else if (!ft_strcmp(str, "\x7f") && delete_last(s) == 1)
		{
			tputs(cursor_left, 1, ft_putchar);
			tputs(delete_character, 1, ft_putchar);
		}
		else if (!ft_strcmp(str, "\3"))
			break ;
		else if (!ft_strcmp(str, "\4") && !*s)
		{
			s = ft_strdup("exit");
			ft_putstr(s);
			break ;
		}
		else if (str[0] >= 20 && str[0] <= 126)
		{
			write(1, str, l);
			ft_realloc(&s, str);
		}
	}
	free(str);
	write(1, "\n", 1);
	return (s);
}
