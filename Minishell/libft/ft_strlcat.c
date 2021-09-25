/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 23:27:23 by gdilly            #+#    #+#             */
/*   Updated: 2021/08/09 23:27:24 by gdilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	g;
	size_t	j;

	g = 0;
	j = 0;
	if (!dst && !src)
		return (0);
	if (ft_strlen(dst) >= size)
		return (size + ft_strlen(src));
	while (dst[g])
		g++;
	while (src[j] && (g + j + 1) < size)
	{
		dst[g + j] = src[j];
		j++;
	}
	dst[g + j] = '\0';
	return (g + ft_strlen(src));
}
