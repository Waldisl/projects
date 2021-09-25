
#include "ft_printf.h"

void		ft_hex16(size_t num, size_t reg, int *length)
{
	size_t	result;

	if (num > 15)
		ft_hex16(num / 16, reg, length);
	result = num % 16;
	if ((result >= 10) && (result <= 15) && (reg == 0))
		print_len((char)result + 87, length);
	else if ((result >= 10) && (result <= 15) && (reg == 1))
		print_len((char)result + 55, length);
	else if (result <= 9)
		print_len((char)result + 48, length);
}

int			ft_length_hex16(size_t num)
{
	int		l;

	l = 0;
	while (num > 15)
	{
		num /= 16;
		l++;
	}
	l++;
	return (l);
}

int			ft_length_prec(int len, int precision)
{
	if (precision >= len)
		return (precision);
	else
		return (len);
}

void		ft_parser_precision(char *fmt, va_list ar, t_param *par)
{
	(*par).dot = 1;
	if (fmt[(*par).i + 1] == '*')
	{
		(*par).i++;
		(*par).precision = va_arg(ar, int);
		if ((*par).precision < -1)
			(*par).precision = -1;
	}
	else if (ft_isdigit(fmt[(*par).i + 1]) == 1)
		ft_precision(par, fmt);
	else
		(*par).precision = 0;
}
