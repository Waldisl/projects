/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msunspot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:23:12 by msunspot          #+#    #+#             */
/*   Updated: 2020/11/19 14:04:11 by msunspot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t s;

	s = 0;
	if (n == 0)
		return (0);
	while (s1[s] == s2[s] && s1[s] != '\0' && s2[s] != '\0' && s < n - 1)
		s++;
	return ((unsigned char)s1[s] - (unsigned char)s2[s]);
}
