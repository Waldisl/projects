
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t		g;
	void		*j;

	g = count * size;
	j = malloc(g);
	if (j)
		ft_memset(j, 0, g);
	return (j);
}
