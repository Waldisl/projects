
#include "libft.h"
#include <string.h>

void	*ft_memset(void *destination, int c, size_t n)
{
	unsigned char	*i;

	i = (unsigned char *)destination;
	while (n > 0)
	{
		*i = (unsigned char)c;
		i++;
		n--;
	}
	return (destination);
}
