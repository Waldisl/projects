
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*p;
	unsigned int	flen;

	flen = ft_strlen(s);
	if (start > flen)
		return (0);
	flen -= start;
	if (flen > len)
		flen = len;
	p = malloc(flen + 1);
	if (!p)
		return (0);
	ft_strlcpy(p, s + start, flen + 1);
	return (p);
}
