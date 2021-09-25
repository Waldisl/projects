
#include "ft_printf.h"

void		ft_processor(const char *s, va_list ar, int *length)
{
	char	*frmt;
	int		d;
	int		i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '%')
		{
			d = i + 1;
			i = ft_type_poz(s, i);
			if (i != 0)
			{
				frmt = ft_substr(s, d, i + 1 - d);
				ft_vtype(ft_parser(frmt, ar), ar, length);
				free(frmt);
			}
			else
				i = d - 1;
		}
		else if (s[i] != '%' && s[i])
			print_len(s[i], length);
	}
}