/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 23:23:54 by gdilly            #+#    #+#             */
/*   Updated: 2021/08/09 23:23:55 by gdilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *arr1, const void *arr2, size_t n)
{
	unsigned char	*g;
	unsigned char	*j;
	size_t			i;

	g = (unsigned char *)arr1;
	j = (unsigned char *)arr2;
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
