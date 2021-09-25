
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		g;

	if (!s1 || !s2)
		return (NULL);
	g = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = (char *)malloc(sizeof(char) * (g));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, (size_t)g);
	ft_strlcat(str, s2, (size_t)g);
	return (str);
}
