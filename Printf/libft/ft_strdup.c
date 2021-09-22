/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msunspot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:25:50 by msunspot          #+#    #+#             */
/*   Updated: 2021/01/21 19:03:28 by msunspot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		s;
	char	*t;

	s = 0;
	while (src[s])
		s++;
	if (!(t = malloc(sizeof(*src) * (s + 1))))
		return (NULL);
	s = 0;
	while (src[s])
	{
		t[s] = src[s];
		s++;
	}
	t[s] = '\0';
	return (t);
}
