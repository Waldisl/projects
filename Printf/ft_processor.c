/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_processor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msunspot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 17:27:10 by msunspot          #+#    #+#             */
/*   Updated: 2021/01/23 19:28:18 by msunspot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_processor(const char *s, va_list ar, int *length)
{
	char	*frmt;
	int		d;
	int		i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '%')
		{
			d = i + 1;
			i = ft_type_poz(s, i);
			if (i != 0)
			{
				frmt = ft_substr(s, d, i + 1 - d);
				ft_vtype(ft_parser(frmt, ar), ar, length);
				free(frmt);
			}
			else
				i = d - 1;
		}
		else if (s[i] != '%' && s[i])
			print_len(s[i], length);
	}
}