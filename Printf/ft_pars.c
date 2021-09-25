
#include "ft_printf.h"

void			ft_width(t_param *par, char *frmt)
{
	(*par).width = ft_atoi(&frmt[(*par).i]);
	while (ft_isdigit(frmt[(*par).i]) == 1 && frmt[(*par).i])
		(*par).i++;
	(*par).i--;
}

void			ft_precision(t_param *par, char *frmt)
{
	(*par).i++;
	(*par).precision = ft_atoi(&frmt[(*par).i]);
	while (ft_isdigit(frmt[(*par).i]) == 1 && frmt[(*par).i])
		(*par).i++;
	(*par).i--;
}

void			ft_type(t_param *par, char *frmt)
{
	if (frmt[(*par).i] == 'c')
		(*par).type = 'c';
	else if (frmt[(*par).i] == 'd')
		(*par).type = 'd';
	else if (frmt[(*par).i] == 'i')
		(*par).type = 'i';
	else if (frmt[(*par).i] == 'e')
		(*par).type = 'e';
	else if (frmt[(*par).i] == 'f')
		(*par).type = 'f';
	else if (frmt[(*par).i] == 'g')
		(*par).type = 'g';
	else if (frmt[(*par).i] == '%')
		(*par).type = '%';
	else if (frmt[(*par).i] == 'X')
		(*par).type = 'X';
	else if (frmt[(*par).i] == 'p')
		(*par).type = 'p';
	else if (frmt[(*par).i] == 's')
		(*par).type = 's';
	else if (frmt[(*par).i] == 'u')
		(*par).type = 'u';
	else if (frmt[(*par).i] == 'x')
		(*par).type = 'x';
}

void			ft_param(char *frmt, va_list ar, t_param *par)
{
	if (frmt[(*par).i] == '-' && (*par).dot != 1)
		(*par).minus = 1;
	else if (frmt[(*par).i] == '0' && (*par).dot != 1)
		(*par).zero = 1;
	else if (frmt[(*par).i] == '*' && (*par).dot != 1)
	{
		(*par).width = va_arg(ar, int);
		if ((*par).width < 0)
		{
			(*par).minus = 1;
			(*par).width *= -1;
		}
	}
	else if (frmt[(*par).i] <= '9' && frmt[(*par).i] >= '0' && (*par).dot != 1)
		ft_width(par, frmt);
	else if (frmt[(*par).i] == '.')
		ft_parser_precision(frmt, ar, par);
	else if (ft_isalpha(frmt[(*par).i]) == 1 || frmt[(*par).i] == '%')
		ft_type(par, frmt);
}

t_param		ft_parser(char *frmt, va_list ar)
{
	t_param	par;

	ft_memset(&par, 0, sizeof(t_param));
	par.precision = -1;
	while (frmt[par.i])
	{
		ft_param(frmt, ar, &par);
		par.i++;
	}
	return (par);
}
