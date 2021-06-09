#include "libft.h"

void	safe_free(void *mem)
{
	if (mem)
		free(mem);
}
