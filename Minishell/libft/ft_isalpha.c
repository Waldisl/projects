
#include "libft.h"

int	ft_isalpha(int ch)
{
	if (ch >= 'A' && ch <= 'Z')
		return (1);
	else if (ch >= 'a' && ch <= 'z')
		return (1);
	else
		return (0);
}
