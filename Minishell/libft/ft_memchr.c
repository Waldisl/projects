/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 23:23:39 by gdilly            #+#    #+#             */
/*   Updated: 2021/08/09 23:23:40 by gdilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *arr, int c, size_t n)
{
	unsigned char		*g;

	g = (unsigned char *)arr;
	while (n--)
	{
		if (*(g++) == (unsigned char)c)
			return ((void *)--g);
	}
	return (0);
}
