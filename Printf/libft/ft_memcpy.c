/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msunspot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:15:53 by msunspot          #+#    #+#             */
/*   Updated: 2020/11/18 15:09:23 by msunspot         ###   ########.fr       */
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
