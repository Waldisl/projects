/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 23:24:28 by gdilly            #+#    #+#             */
/*   Updated: 2021/08/09 23:24:36 by gdilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *destination, const void *source, size_t n)
{
	unsigned char		*g;
	const unsigned char	*j;
	size_t				i;

	g = (unsigned char *)destination;
	j = (unsigned char *)source;
	i = 0;
	if (!destination && !source)
		return (NULL);
	if (j < g)
		while (i++ < n)
			g[n - i] = j[n - i];
	else
	{
		while (n > 0)
		{
			*(g++) = *(j++);
			n--;
		}
	}
	return (destination);
}
