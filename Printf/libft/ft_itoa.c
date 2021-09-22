/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msunspot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 01:25:09 by msunspot          #+#    #+#             */
/*   Updated: 2021/01/21 22:25:39 by msunspot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(long c)
{
	int len;

	len = 0;
	if (c == 0)
		return (1);
	if (c < 0)
	{
		c = -c;
		len++;
	}
	while (c)
	{
		c /= 10;
		len++;
	}
	return (len);
}

char		*ft_itoa(size_t n)
{
	char	*s;
	int		len;

	len = ft_intlen(n) + 1;
	if (!(s = (char*)malloc(sizeof(char) * len)))
		return (NULL);
	s[len - 1] = '\0';
	if (n == 0)
		s[0] = '0';
	else if (n < 1)
	{
		s[0] = '-';
		n = -n;
	}
	while (n)
	{
		len--;
		s[len - 1] = (n % 10) + '0';
		n = n / 10;
	}
	return (s);
}
