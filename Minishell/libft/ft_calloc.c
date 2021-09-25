/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 23:20:04 by gdilly            #+#    #+#             */
/*   Updated: 2021/08/09 23:20:11 by gdilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t		g;
	void		*j;

	g = count * size;
	j = malloc(g);
	if (j)
		ft_memset(j, 0, g);
	return (j);
}
