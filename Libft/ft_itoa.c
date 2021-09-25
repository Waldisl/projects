
#include "libft.h"

static int	ft_intlen(int c)
{
	int len;

	len = 0;
	if (c == 0)
		return (1);
	if (c < 0)
	{
		c = -c;
		len++;
	}
	while (c)
	{
		c /= 10;
		len++;
	}
	return (len);
}

char		*ft_itoa(int n)
{
	char		*s;
	size_t		len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = ft_intlen(n) + 1;
	if (!(s = (char*)malloc(sizeof(char) * len)))
		return (NULL);
	if (n == 0)
		s[0] = '0';
	if (n < 0)
	{
		s[0] = '-';
		n = -n;
	}
	s[len - 1] = '\0';
	while (n)
	{
		len--;
		s[len - 1] = (n % 10) + '0';
		n /= 10;
	}
	return (s);
}
