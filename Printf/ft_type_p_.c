/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_p_.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msunspot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 22:53:32 by msunspot          #+#    #+#             */
/*   Updated: 2021/01/24 13:21:32 by msunspot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void			ft_min(unsigned long n, int len, t_param par, int *length)
{
	char			*s;
	int				num;

	s = "0x";
	if (n == 0 && par.precision == 0)
		num = 0;
	else
		num = len;
	while (*s)
		print_len(*s++, length);
	if (n || (par.precision != 0 && !n))
		ft_hex16(n, 0, length);
	while (par.width-- > num + 2)
		print_len(' ', length);
}

static void			ft_fl(unsigned long n, int len, t_param par, int *length)
{
	char			*s;

	s = "0x";
	if (n == 0 && par.precision == 0)
		len = 0;
	while (par.width-- > ft_length_prec(len, par.precision) + 2)
		print_len(' ', length);
	len += 2;
	while (*s)
		print_len(*s++, length);
	while (par.precision > ft_length_prec(len, par.precision) - 2)
	{
		print_len('0', length);
		par.precision--;
	}
	if (n || (par.precision != 0 && !n))
		ft_hex16(n, 0, length);
}

void				ft_type_p(t_param par, va_list ar, int *length)
{
	int				len;
	unsigned long	n;

	n = va_arg(ar, unsigned long);
	len = ft_length_hex16(n);
	if (par.minus == 1)
		ft_min(n, len, par, length);
	else
		ft_fl(n, len, par, length);
}
