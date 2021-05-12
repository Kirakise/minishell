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
			return (ft_strdup(""));
			//return (0);
		}
		*lst = el->prev;
	}
	el = *lst;//
	return (el->content);
}

void history_free(t_2list **hist)
{
	t_2list *el;

	if (!hist || !*hist)
		return ;
	el = *hist;
	while (el->prev)
		el = el->prev;
	*hist = el;
	tlist_destroy(hist);
}
