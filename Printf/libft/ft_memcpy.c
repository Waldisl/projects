
#include "libft.h"

void	*ft_memcpy(void *destination, const void *source, size_t n)
{
	unsigned char		*g;
	const unsigned char	*j;

	g = (unsigned char *)destination;
	j = (unsigned char *)source;
	if (!destination && !source)
		return (NULL);
	while (n > 0)
	{
		*(g++) = *(j++);
		n--;
	}
	return (destination);
}
