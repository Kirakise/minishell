#include "../../includes/minishell.h"
#include <signal.h>

extern t_shell	g_shell;

void	handlesigint(int a)
{
	if (a == SIGINT)
		waitpid(-1, &g_shell.status, WNOHANG);
}

int	setinit(struct termios *term)
{
	char	*term_name;

	term_name = find_var("TERM");
	if (!term_name || tcgetattr(0, term) == -1)
		return (1);
	term->c_lflag &= ~(ECHO);
	term->c_lflag &= ~(ICANON);
	term->c_cc[VMIN] = 1;
	term->c_cc[VTIME] = 0;
	signal(SIGINT, handlesigint);
	if (tgetent(0, term_name) == -1 || tcsetattr(0, TCSANOW, term) == -1)
		return (-1);
	if (term_name)
		free(term_name);
	return (0);
}

void	setic(struct termios *term)
{
	term->c_lflag &= ~(ECHO);
	term->c_lflag &= ~(ICANON);
	term->c_lflag &= ~(ISIG);
	tcsetattr(0, TCSANOW, term);
}

void	setc(struct termios *term)
{
	term->c_lflag |= (ECHO);
	term->c_lflag |= (ICANON);
	term->c_lflag |= (ISIG);
	tcsetattr(0, TCSANOW, term);
}
