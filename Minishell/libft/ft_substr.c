/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 23:30:14 by gdilly            #+#    #+#             */
/*   Updated: 2021/08/09 23:30:16 by gdilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*p;
	unsigned int	flen;

	flen = ft_strlen(s);
	if (start > flen)
		return (0);
	flen -= start;
	if (flen > len)
		flen = len;
	p = malloc(flen + 1);
	if (!p)
		return (0);
	ft_strlcpy(p, s + start, flen + 1);
	return (p);
}
