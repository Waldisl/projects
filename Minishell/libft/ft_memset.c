/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 23:24:49 by gdilly            #+#    #+#             */
/*   Updated: 2021/08/09 23:24:50 by gdilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	*ft_memset(void *destination, int c, size_t n)
{
	unsigned char	*i;

	i = (unsigned char *)destination;
	while (n > 0)
	{
		*i = (unsigned char)c;
		i++;
		n--;
	}
	return (destination);
}
