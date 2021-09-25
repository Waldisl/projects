/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 23:26:57 by gdilly            #+#    #+#             */
/*   Updated: 2021/08/09 23:26:58 by gdilly           ###   ########.fr       */
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
	t = malloc(sizeof(*src) * (s + 1));
	if (!(t))
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
