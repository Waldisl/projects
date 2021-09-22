/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_di_.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msunspot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 22:50:52 by msunspot          #+#    #+#             */
/*   Updated: 2021/01/24 13:21:16 by msunspot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_minus_d_i(char *s, long n, t_param par, int *length)
{
	int			i;
	int			num;
	int			len;

	len = ft_strlen(s);
	i = 0;
	num = ft_length_prec(len, par.precision);
	if (n < 0)
	{
		print_len('-', length);
		par.width--;
	}
	while (par.precision-- > len)
		print_len('0', length);
	while (i < len)
		print_len(s[i++], length);
	while (par.width-- - num > 0)
		print_len(' ', length);
}

static void		ft_zero_d_i(char *s, long n, t_param par, int *length)
{
	int			i;
	int			len;

	len = ft_strlen(s);
	i = 0;
	if (n < 0)
	{
		print_len('-', length);
		par.width--;
	}
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

static void		ft_flag_d_i(char *s, long n, t_param par, int *length)
{
	int			i;
	int			num;
	int			len;

	len = ft_strlen(s);
	i = 0;
	num = ft_length_prec(len, par.precision);
	if (n < 0)
		par.width--;
	while (par.width-- - num > 0)
		print_len(' ', length);
	if (n < 0)
		print_len('-', length);
	while (par.precision-- > len)
		print_len('0', length);
	while (i < len)
		print_len(s[i++], length);
}

void			ft_type_d_i(t_param par, va_list ar, int *length)
{
	char		*s;
	long int	n;

	if (par.precision > -1)
		par.zero = 0;
	n = va_arg(ar, int);
	s = ft_itoa(n);
	if (n < 0)
		s = ft_itoa(n * (-1));
	if (par.precision == 0 && par.width > 0 && n == 0)
	{
		while (par.width-- > 0)
			print_len(' ', length);
	}
	else if (par.precision == 0 && par.width == 0 && n == 0)
		*length += 0;
	else if (par.minus == 1)
		ft_minus_d_i(s, n, par, length);
	else if (par.zero == 1)
		ft_zero_d_i(s, n, par, length);
	else if (par.minus == 0 && par.zero == 0)
		ft_flag_d_i(s, n, par, length);
	free(s);
}
