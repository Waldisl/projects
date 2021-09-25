
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		len;
	char	*p;

	while (*s1 && ft_strchr(set, *s1))
		s1++;
	len = ft_strlen(s1);
	while (*s1 && ft_strchr(set, s1[len - 1]))
		len--;
	p = malloc(len + 1);
	if (p)
		ft_strlcpy(p, s1, len + 1);
	return (p);
}
