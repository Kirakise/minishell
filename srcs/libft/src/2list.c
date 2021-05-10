#include "../../../includes/libft.h"

t_2list	*tlist_new(void *content)
{
	t_2list	*el;

	if (!(el = malloc(sizeof(t_2list))))
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
	if (el)
		el->prev = new;
	new->next = el;
	el = new;
	*lst = el;
}
