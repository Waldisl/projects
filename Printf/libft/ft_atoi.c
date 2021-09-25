
#include "libft.h"

int		ft_atoi(char *str)
{
	int a;
	int b;

	b = 1;
	a = 0;
	while (*str && (*str == ' ' || *str == '\n' || *str == '\t' || \
				*str == '\v' || *str == '\f' || *str == '\r'))
		str++;
	if (*str == '-')
		b = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str && *str >= '0' && *str <= '9')
	{
		if ((a * 10) < a)
			return ((b < 1) ? 0 : -1);
		a = a * 10 + (*str - 48);
		str++;
	}
	return (a * b);
}
