/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msunspot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:15:11 by msunspot          #+#    #+#             */
/*   Updated: 2020/11/04 15:33:59 by msunspot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	*ft_memset(void *destination, int c, size_t n)
{
	unsigned char *i;

	i = (unsigned char*)destination;
	while (n > 0)
	{
		*i = (unsigned char)c;
		i++;
		n--;
	}
	return (destination);
}
