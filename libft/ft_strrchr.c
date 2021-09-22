/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msunspot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:19:17 by msunspot          #+#    #+#             */
/*   Updated: 2020/11/19 14:02:06 by msunspot         ###   ########.fr       */
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
			g = (char*)str;
		str++;
	}
	if (g)
		return (g);
	if (ch == '\0')
		return ((char*)str);
	return (0);
}
