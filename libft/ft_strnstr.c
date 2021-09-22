/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msunspot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:19:31 by msunspot          #+#    #+#             */
/*   Updated: 2020/11/18 22:43:41 by msunspot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	g;
	size_t	j;

	g = 0;
	if (!*little)
		return ((char*)big);
	while (big[g] != '\0' && g < len)
	{
		if (big[g] == little[0])
		{
			j = 1;
			while (little[j] != '\0' && big[g + j] == little[j] && \
					(g + j) < len)
				j++;
			if (little[j] == '\0')
				return ((char*)&big[g]);
		}
		g++;
	}
	return (0);
}
