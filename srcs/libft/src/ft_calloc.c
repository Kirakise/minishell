#include "../../../includes/libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;

	if (!(mem = malloc(count * size)))
		return (0);
	ft_bzero(mem, count * size);
	return (mem);
}
