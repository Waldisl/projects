/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msunspot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 16:21:45 by msunspot          #+#    #+#             */
/*   Updated: 2021/01/24 13:32:24 by msunspot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		print_len(char c, int *length)
{
	ft_putchar_fd(c, 1);
	(*length)++;
}

int			ft_type_poz(const char *s, int i)
{
	while (s[++i])
	{
		if ((ft_isalpha(s[i]) == 1) || s[i] == '%')
		{
			if (s[i] == 's' || s[i] == 'd' || s[i] == 'i' || s[i] == 'e')
				return (i);
			else if (s[i] == 'f' || s[i] == 'g' || s[i] == 'n' || s[i] == 'u')
				return (i);
			else if (s[i] == '%' || s[i] == 'c' || s[i] == 'X' || s[i] == 'x')
				return (i);
			else if (s[i] == 'p')
				return (i);
			else
				return (0);
		}
	}
	return (0);
}

void		ft_vtype(t_param par, va_list ar, int *length)
{
	if (par.type == 'c')
		ft_type_c(par, ar, length);
	else if (par.type == 'd' || par.type == 'i')
		ft_type_d_i(par, ar, length);
	else if (par.type == '%')
		ft_type_proc(par, length);
	else if (par.type == 'p')
		ft_type_p(par, ar, length);
	else if (par.type == 's')
		ft_type_s(par, ar, length);
	else if (par.type == 'u')
		ft_type_u(par, ar, length);
	else if (par.type == 'x' || par.type == 'X')
		ft_type_x(par, ar, length);
}

int			ft_printf(const char *s, ...)
{
	va_list	ar;
	int		length;

	if (s == NULL)
		return (-1);
	va_start(ar, s);
	length = 0;
	ft_processor(s, ar, &length);
	va_end(ar);
	return (length);
}
