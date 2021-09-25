/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 23:24:10 by gdilly            #+#    #+#             */
/*   Updated: 2021/08/09 23:24:11 by gdilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *destination, const void *source, size_t n)
{
	unsigned char		*g;
	const unsigned char	*j;

	g = (unsigned char *)destination;
	j = (unsigned char *)source;
	if (!destination && !source)
		return (NULL);
	while (n > 0)
	{
		*(g++) = *(j++);
		n--;
	}
	return (destination);
}
