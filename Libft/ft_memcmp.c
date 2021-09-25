/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msunspot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:17:14 by msunspot          #+#    #+#             */
/*   Updated: 2020/11/18 22:32:05 by msunspot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *arr1, const void *arr2, size_t n)
{
	unsigned char	*g;
	unsigned char	*j;
	size_t			i;

	g = (unsigned char*)arr1;
	j = (unsigned char*)arr2;
	i = 0;
	if (n == 0)
		return (0);
	while (*g == *j && ++i < n)
	{
		g++;
		j++;
	}
	return ((int)*g - (int)*j);
}
