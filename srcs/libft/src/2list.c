#include "libft.h"

t_2list	*tlist_new(void *content)
{
	t_2list	*el;

	el = malloc(sizeof(t_2list));
	if (!el)
		return (0);
	el->content = content;
	el->next = 0;
	el->prev = 0;
	return (el);
}

void	tlist_add_front(t_2list **lst, t_2list *new)
{
	t_2list	*el;

	if (!lst)
		return ;
	el = *lst;
	new->next = el;
	if (el)
		el->prev = new;
	el = new;
	*lst = el;
}

int	tlist_destroy(t_2list **lst)
{
	t_2list	*el;
	t_2list	*tmp;

	if (!lst || !*lst)
		return (-1);
	el = *lst;
	while (el)
	{
		tmp = el->next;
		el->content = 0;
		free(el->content);
		el->next = 0;
		el->prev = 0;
		free(el);
		el = tmp;
	}
	return (0);
}

/*
t_2list	*tlist_last(t_2list *lst)
{
	t_2list	*el;

	if (!lst)
		return (0);
	el = lst;
	while (el->next)
		el = el->next;
	return (el);
}

int		tlist_add_back(t_2list **lst, t_2list *new)
{
	t_2list	*el;

	if (!lst || !new)
		return (-1);
	if (!*lst)
	{
		*lst = new;
		return (0);
	}
	el = ft_lstlast(*lst);
	el->next = new;
	return (0);
}
*/
