#include "minishell.h"
t_shell	g_shell;
int main()
{
	char **line;
	char *s;
	while (true)
	{
		s = get_next_line(0);
		line = tvoipars(s);
	}
}
