#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*el;

	if (!(el = malloc(sizeof(t_list))))
		return (0);
	el->content = content;
	el->next = 0;
	return (el);
}

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*el;

	if (!lst)
		return (0);
	el = lst;
	while (el->next)
		el = el->next;
	return (el);
}

int	ft_lst_getsize(t_list *lst)
{
	t_list	*el;
	int		i;

	if (!lst)
		return (0);
	el = lst;
	i = 1;
	while (el->next)
	{
		el = el->next;
		i++;
	}
	return (i);
}

int		ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*el;

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

int		ft_lstdestroy(t_list **lst)
{
	t_list	*el;
	t_list	*tmp;

	if (!lst || !*lst)
		return (-1);
	el = *lst;
	while (el)
	{
		tmp = el->next;
		el->content = 0;
		el->next = 0;
		free(el);
		el = tmp;
	}
	return (0);
}
