
#include "libft.h"

void	*ft_memchr(const void *arr, int c, size_t n)
{
	unsigned char		*g;

	g = (unsigned char *)arr;
	while (n--)
	{
		if (*(g++) == (unsigned char)c)
			return ((void *)--g);
	}
	return (0);
}
