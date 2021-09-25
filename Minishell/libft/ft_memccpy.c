
#include "libft.h"

void	*ft_memccpy(void *destination, const void *source, int c, size_t n)
{
	unsigned char		*g;
	const unsigned char	*j;
	unsigned char		l;
	size_t				i;

	g = (unsigned char *)destination;
	j = (unsigned char *)source;
	l = (unsigned char)c;
	i = 0;
	while (n > i)
	{
		g[i] = j[i];
		if (g[i] == l)
			return ((void *)(destination + i + 1));
		i++;
	}
	return (NULL);
}
