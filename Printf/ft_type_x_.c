/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_x_.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msunspot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 23:05:48 by msunspot          #+#    #+#             */
/*   Updated: 2021/01/24 13:33:45 by msunspot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void			ft_minus_x(size_t n, int reg, t_param par, int *length)
{
	int			num;
	int			len;

	len = ft_length_hex16(n);
	num = ft_length_prec(len, par.precision);
	while (par.precision-- > len)
		print_len('0', length);
	ft_hex16(n, reg, length);
	while (par.width-- - num > 0)
		print_len(' ', length);
}

static void			ft_zero_x(size_t n, int reg, t_param par, int *length)
{
	int				len;

	len = ft_length_hex16(n);
	if (par.width > len)
	{
		while (par.width-- - len)
			print_len('0', length);
		ft_hex16(n, reg, length);
	}
	else
		ft_hex16(n, reg, length);
}

static void			ft_flag_x(size_t n, int reg, t_param par, int *length)
{
	int				num;
	int				len;

	len = ft_length_hex16(n);
	num = ft_length_prec(len, par.precision);
	while (par.width-- - num > 0)
		print_len(' ', length);
	while (par.precision-- > len)
		print_len('0', length);
	ft_hex16(n, reg, length);
}

void				ft_type_x(t_param par, va_list ar, int *length)
{
	unsigned int	n;
	int				reg;

	if (par.precision > -1)
		par.zero = 0;
	n = va_arg(ar, unsigned int);
	reg = 0;
	if (par.type == 'X')
		reg = 1;
	if (par.precision == 0 && !n)
	{
		while (par.width-- > 0)
			print_len(' ', length);
	}
	else if (par.precision == 0 && par.width == 0 && !n)
		*length += 0;
	else if (par.minus == 1)
		ft_minus_x(n, reg, par, length);
	else if (par.zero == 1)
		ft_zero_x(n, reg, par, length);
	else if (par.minus == 0 && par.zero == 0)
		ft_flag_x(n, reg, par, length);
}
