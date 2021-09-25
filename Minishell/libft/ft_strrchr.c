/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 23:29:51 by gdilly            #+#    #+#             */
/*   Updated: 2021/08/09 23:32:02 by gdilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int ch)
{
	char	*g;

	g = 0;
	while (*str)
	{
		if (*str == ch)
			g = (char *)str;
		str++;
	}
	if (g)
		return (g);
	if (ch == '\0')
		return ((char *)str);
	return (0);
}
