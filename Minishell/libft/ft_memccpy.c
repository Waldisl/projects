/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 23:23:25 by gdilly            #+#    #+#             */
/*   Updated: 2021/08/09 23:23:27 by gdilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *destination, const void *source, int c, size_t n)
{
	unsigned char		*g;
	const unsigned char	*j;
	unsigned char		l;
	size_t				i;

	g = (unsigned char *)destination;
	j = (unsigned char *)source;
	l = (unsigned char)c;
	i = 0;
	while (n > i)
	{
		g[i] = j[i];
		if (g[i] == l)
			return ((void *)(destination + i + 1));
		i++;
	}
	return (NULL);
}
