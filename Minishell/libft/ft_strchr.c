
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*ss;

	if (!s)
		return (0);
	ss = (char *)s;
	while (*ss != (char)c)
	{
		if (*ss == 0)
			return (0);
		ss++;
	}
	return (ss);
}
