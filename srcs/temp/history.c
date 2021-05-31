#include "../../includes/minishell.h"

void	history_update(t_2list **hist, char *s)
{
	t_2list	*el;

	if (!s)
		return ;
	if (!*s)
	{
		free(s);
		return ;
	}
	if (hist && *hist)
	{
		el = *hist;
		while (el->prev)
			el = el->prev;
		*hist = el;
	}
	tlist_add_front(hist, tlist_new(s));
}

char	*get_history_line(t_2list **lst, int dir, int *end)
{
	t_2list	*el;

	if (!lst || !*lst)
		return (ft_strdup(""));
	el = *lst;
	if (*end == 0 && dir == 1)
	{
		*end = 1;
		return (ft_strdup(el->content));
	}
	if (dir == 1 && el->next)
		*lst = el->next;
	else if (dir == -1)
	{
		if (!el->prev)
		{
			*end = 0;
			return (ft_strdup(""));
		}
		*lst = el->prev;
	}
	el = *lst;
	return (ft_strdup(el->content));
}

void	history_free(t_2list **hist)
{
	t_2list	*el;

	if (!hist || !*hist)
		return ;
	el = *hist;
	while (el->prev)
		el = el->prev;
	*hist = el;
	tlist_destroy(hist);
}
