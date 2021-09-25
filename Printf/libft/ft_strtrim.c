
#include "libft.h"

static int	ft_set(char const *str, char const ar)
{
	size_t		t;

	t = 0;
	while (str[t])
	{
		if (str[t] == ar)
			return (1);
		t++;
	}
	return (0);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	size_t		i;
	size_t		k;
	size_t		it;
	char		*m;

	if (!s1 || !set)
		return (NULL);
	i = ft_strlen(s1);
	k = 0;
	while (s1[k] && ft_set(set, s1[k]))
		k++;
	while (i > k && ft_set(set, s1[i - 1]))
		i--;
	m = malloc(sizeof(*s1) * (i - k + 1));
	if (!m)
		return (NULL);
	it = 0;
	while (k < i)
		m[it++] = s1[k++];
	m[it] = '\0';
	return (m);
}
