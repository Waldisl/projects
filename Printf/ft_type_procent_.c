/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_procent_.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msunspot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 23:02:01 by msunspot          #+#    #+#             */
/*   Updated: 2021/01/23 21:42:23 by msunspot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_minus_proc(t_param par, int *length)
{
	print_len('%', length);
	while (par.width-- - 1 > 0)
		print_len(' ', length);
}

static void		ft_zero_proc(t_param par, int *length)
{
	while (par.width-- - 1 > 0)
		print_len('0', length);
	print_len('%', length);
}

static void		ft_flag_proc(t_param par, int *length)
{
	while (par.width-- - 1 > 0)
		print_len(' ', length);
	print_len('%', length);
}

void			ft_type_proc(t_param par, int *length)
{
	if (par.minus == 1)
		ft_minus_proc(par, length);
	else if (par.zero == 1)
		ft_zero_proc(par, length);
	else
		ft_flag_proc(par, length);
}
