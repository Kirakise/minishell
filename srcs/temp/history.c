#include "../../includes/minishell.h"

void history_update(t_2list **hist, char *s)
{
	t_2list	*el;

	if (s && *s)
	{
/*
		if (!ft_strcmp(el->content, s))
			return ;
*/
		if (hist && *hist)
		{
			el = *hist;
			while (el->prev)
				el = el->prev;
			*hist = el;
		}
		tlist_add_front(hist, tlist_new(s));
	}
}

char *get_history_line(t_2list **lst, int dir, int *end)
{
	t_2list *el;

	if (!lst || !*lst)
		return (0);
	el = *lst;
	if (*end == 0 && dir == 1)
	{
		*end = 1;
		return (el->content);
	}
	if (dir == 1 && el->next)
		*lst = el->next;
	else if (dir == -1)
	{
		if (!el->prev)
		{
			*end = 0;
			return ("");
			//return (0);
		}
		*lst = el->prev;
	}
	el = *lst;//
	return (el->content);
}

/*
int history_init(t_history *hist)
{
	hist->arr = ft_calloc(HISTORY_SIZE, sizeof(char *));
	if (!hist->arr)
		return (1);
	hist->i = 0;
	hist->last = 0;
	return (0);
}

char *get_history_line(int direction)
{
	static char **hist = 0;
	static int	i = 0;
	int			last;

	last = get_history_len();
	if ((i + direction) >= 0 && (i + direction) <= last)
		i += direction;
	return (hist[i]);
}

int history_update(t_history *hist, char *s)
{
	if (hist->last == HISTORY_SIZE)

	return (0);
}
*/
