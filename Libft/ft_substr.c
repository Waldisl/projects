
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*g;
	size_t	i;

	if (!s)
		return (NULL);
	if ((size_t)start >= ft_strlen(s))
		return (ft_strdup(""));
	g = malloc(sizeof(char) * (len + 1));
	i = 0;
	if (!g)
		return (NULL);
	while (i < len)
	{
		g[i] = s[start + i];
		i++;
	}
	g[i] = '\0';
	return (g);
}
