
#include "ft_printf.h"

static int	ft_len_prec(int l, int precision)
{
	if (precision >= l)
		return (l);
	else
		return (precision);
}

static void	ft_minus_s(char *s, int len, t_param par, int *length)
{
	int		i;

	i = 0;
	if (par.precision == 0)
	{
		while (par.width-- > 0)
			print_len(' ', length);
	}
	else if (par.precision > 0)
	{
		while (i < len && i < par.precision)
			print_len(s[i++], length);
		while (par.width-- - ft_len_prec(len, par.precision) > 0)
			print_len(' ', length);
	}
	else if (par.precision == -1)
	{
		while (i < len)
			print_len(s[i++], length);
		while (par.width-- - len > 0)
			print_len(' ', length);
	}
}

static void	ft_zero_s(char *s, int len, t_param par, int *length)
{
	int		i;

	i = 0;
	if (par.precision == 0)
	{
		while (par.width-- > 0)
			print_len('0', length);
	}
	else if (par.precision > 0)
	{
		while (par.width-- - ft_len_prec(len, par.precision) > 0)
			print_len('0', length);
		while (i < len && i < par.precision)
			print_len(s[i++], length);
	}
	else if (par.precision == -1)
	{
		while (par.width-- - len > 0)
			print_len('0', length);
		while (i < len)
			print_len(s[i++], length);
	}
}

static void	ft_flag_s(char *s, int len, t_param par, int *length)
{
	int		i;

	i = 0;
	if (par.precision == 0)
	{
		while (par.width-- > 0)
			print_len(' ', length);
	}
	else if (par.precision > 0)
	{
		while (par.width-- - ft_len_prec(len, par.precision) > 0)
			print_len(' ', length);
		while (i < len && i < par.precision)
			print_len(s[i++], length);
	}
	else if (par.precision == -1)
	{
		while (par.width-- - len > 0)
			print_len(' ', length);
		while (i < len)
			print_len(s[i++], length);
	}
}

void		ft_type_s(t_param par, va_list ar, int *length)
{
	char	*s;
	int		len;

	s = va_arg(ar, char*);
	if (!s)
		s = "(null)";
	len = ft_strlen(s);
	if (par.precision == 0 && par.width == 0)
		*length += 0;
	else if (par.minus == 1)
		ft_minus_s(s, len, par, length);
	else if (par.zero == 1)
		ft_zero_s(s, len, par, length);
	else
		ft_flag_s(s, len, par, length);
}
