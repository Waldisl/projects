
#include "libft.h"

char	*ft_strrchr(const char *str, int ch)
{
	char	*g;

	g = 0;
	while (*str)
	{
		if (*str == ch)
			g = (char*)str;
		str++;
	}
	if (g)
		return (g);
	if (ch == '\0')
		return ((char*)str);
	return (0);
}
