
#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		s;
	char	*t;

	s = 0;
	while (src[s])
		s++;
	t = malloc(sizeof(*src) * (s + 1));
	if (!(t))
		return (NULL);
	s = 0;
	while (src[s])
	{
		t[s] = src[s];
		s++;
	}
	t[s] = '\0';
	return (t);
}
