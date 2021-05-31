#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*cdst;
	const unsigned char	*csrc;

	if (dst || src)
	{
		cdst = (unsigned char *)dst;
		csrc = (const unsigned char *)src;
		if (cdst < csrc)
			while (len-- > 0)
				*cdst++ = *csrc++;
		else
		{
			cdst += len - 1;
			csrc += len - 1;
			while (len-- > 0)
				*cdst-- = *csrc--;
		}
	}
	return (dst);
}
