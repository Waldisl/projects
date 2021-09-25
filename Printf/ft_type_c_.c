
#include "ft_printf.h"

static void	ft_minus_c(int s, t_param par, int *length)
{
	print_len(s, length);
	while (par.width-- > 1)
		print_len(' ', length);
}

static void	ft_zero_c(int s, t_param par, int *length)
{
	while (par.width-- > 1)
		print_len('0', length);
	print_len(s, length);
}

static void	ft_no_flag_c(int s, t_param par, int *length)
{
	while (par.width-- > 1)
		print_len(' ', length);
	print_len(s, length);
}

void		ft_type_c(t_param par, va_list ar, int *length)
{
	int s;

	s = va_arg(ar, int);
	if (par.minus == 1)
		ft_minus_c(s, par, length);
	else if (par.zero == 1)
		ft_zero_c(s, par, length);
	else
		ft_no_flag_c(s, par, length);
}
