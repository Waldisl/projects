/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msunspot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 16:42:00 by msunspot          #+#    #+#             */
/*   Updated: 2020/12/22 16:42:00 by msunspot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	g;
	size_t	j;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	g = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = (char *)malloc(sizeof(char) * (g));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, (size_t)g);
	if (ft_strlen(s2) >= (size_t)g)
		return (str);
	i = 0;
	j = 0;
	while (str[i])
		i++;
	while (s2[j] && (i + j + 1) < (size_t)g)
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

char	*ft_strnew(size_t size)
{
	char	*str;
	size_t	i;

	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < size)
	{
		str[size] = '\0';
		size--;
	}
	str[0] = '\0';
	return (str);
}

size_t	ft_strlen(const char *str)
{
	size_t a;

	a = 0;
	while (str[a] != '\0')
		a++;
	return (a);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t i;

	i = 0;
	if (!src)
		return (0);
	if (dstsize == 0)
		return (ft_strlen(src));
	while (src[i] != '\0' && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

char	*ft_strchr(const char *str, int ch)
{
	while (*str)
	{
		if (*str == ch)
			return ((char *)str);
		str++;
	}
	if (ch == '\0')
		return ((char *)str);
	return (0);
}
