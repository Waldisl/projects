
#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	a;

	if (!str)
		return (0);
	a = 0;
	while (str[a] != '\0')
		a++;
	return (a);
}
