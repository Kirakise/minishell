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

char *tmpread()
{
	int l;
	int end = 0;
	char *str;
	char *s;
	char *tmp;

	s = ft_calloc(1, 1);
	tputs(save_cursor, 1, ft_putchar);
	do
		{
			tmp = 0;
			str = ft_calloc(100, 1);
			l = read(g_shell.tmp_fd_0, str, 5);
			if (!ft_strcmp(str, "\e[A") || !ft_strcmp(str, "\e[B"))
			{
				tputs(restore_cursor, g_shell.tmp_fd_1, ft_putchar);
				tputs(tigetstr("ed"), 1, ft_putchar);
				if (!ft_strcmp(str, "\e[A"))
					tmp = get_history_line(&g_shell.hist, 1, &end);
				else
					tmp = get_history_line(&g_shell.hist, -1, &end);
				if (tmp)
				{
					s = tmp;
					tmp = 0;
					write(g_shell.tmp_fd_1, s, ft_strlen(s));
				}
			}
			else if (!ft_strcmp(str, "\x7f"))
			{
				if (delete_last(s) == 1)
				{
					tputs(cursor_left, 1, ft_putchar);
					tputs(delete_character, 1, ft_putchar);
				}
			}
			else if (!ft_strcmp(str, "\3"))
			{
				free(str);
				break ;
			}
			else if (!ft_strcmp(str, "\4") && s[0] == 0)
				exit(0);
			else if (str[0] >= 20 && str[0] <= 126)
			{
				write(1, str, l);
				s = ft_realloc(s, str);//а вот тут все очень любит крашиться, это прям топ место
			}
			//free(str); вот с этим все адски крашилось при fsanitize=address
		} while (ft_strcmp(str, "\n"));
	write(1, "\n", 1);
	return (s);
}
