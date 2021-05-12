#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <signal.h>
extern t_shell g_shell;
void handlesigint(int a)
{
    if (a == 3)
        kill(g_shell.pidt, SIGINT);
}

int setinit(struct termios *term)
{
    char *term_name;

    term_name = find_var("TERM");
	if (tcgetattr(0, term) == -1)
        return (1);
	term->c_lflag &= !(ECHO);
	term->c_lflag &= !(ICANON);
	// term->c_cc[VMIN] = 1;
	// term->c_cc[VTIME] = 0;
    // signal(SIGINT, handlesigint);
	if (tgetent(0, term_name) == -1 || tcsetattr(0, TCSANOW, term) == -1)
        return (-1);
    free(term_name);
    return (0);
}

void setic(struct termios *term)
{
	term->c_lflag &= !(ECHO);
	term->c_lflag &= !(ICANON);
    tcsetattr(0, TCSANOW, term);
}

void setc(struct termios *term)
{
	term->c_lflag |= (ECHO);
	term->c_lflag |= (ICANON);
    tcsetattr(0, TCSANOW, term);
}