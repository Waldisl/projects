
#include "ft_printf.h"

static void			ft_minus_u(char *s, int len, t_param par, int *length)
{
	int				i;
	int				num;

	i = 0;
	num = ft_length_prec(len, par.precision);
	while (par.precision-- > len)
		print_len('0', length);
	while (i < len)
		print_len(s[i++], length);
	while (par.width-- - num > 0)
		print_len(' ', length);
}

static void			ft_zero_u(char *s, int len, t_param par, int *length)
{
	int				i;

	i = 0;
	if (par.width > len)
	{
		while (par.width-- - len)
			print_len('0', length);
		while (i < len)
			print_len(s[i++], length);
	}
	else
	{
		while (i < len)
			print_len(s[i++], length);
	}
}

static void			ft_flag_u(char *s, int len, t_param par, int *length)
{
	int				i;
	int				num;

	i = 0;
	num = ft_length_prec(len, par.precision);
	while (par.width-- - num > 0)
		print_len(' ', length);
	while (par.precision-- > len)
		print_len('0', length);
	while (i < len)
		print_len(s[i++], length);
}

void				ft_type_u(t_param par, va_list ar, int *length)
{
	char			*s;
	int				len;
	unsigned int	n;

	if (par.precision > -1)
		par.zero = 0;
	n = va_arg(ar, unsigned int);
	s = ft_itoa(n);
	len = ft_strlen(s);
	if (par.precision == 0 && !n)
	{
		while (par.width-- > 0)
			print_len(' ', length);
	}
	else if (par.precision == 0 && par.width == 0 && !n)
		*length += 0;
	else if (par.minus == 1)
		ft_minus_u(s, len, par, length);
	else if (par.zero == 1)
		ft_zero_u(s, len, par, length);
	else if (par.minus == 0 && par.zero == 0)
		ft_flag_u(s, len, par, length);
	free(s);
}
