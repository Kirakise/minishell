#include "libft.h"

void	**lst_to_arr(t_list *lst)
{
	int		size;
	int		i;
	t_list	*lst_tmp;
	void	**arr;

	lst_tmp = lst;
	size = ft_lst_getsize(lst);
	arr = malloc(sizeof(t_list) * (size + 1));
	if (!arr)
		return (0);
	i = 0;
	while (lst)
	{
		arr[i] = lst->content;
		i++;
		lst = lst->next;
	}
	arr[i] = 0;
	ft_lstdestroy(&lst_tmp, 0);
	return (arr);
}
