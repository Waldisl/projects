/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msunspot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:16:59 by msunspot          #+#    #+#             */
/*   Updated: 2020/11/18 16:24:02 by msunspot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *arr, int c, size_t n)
{
	unsigned char		*g;

	g = (unsigned char*)arr;
	while (n--)
	{
		if (*(g++) == (unsigned char)c)
			return ((void*)--g);
	}
	return (0);
}
