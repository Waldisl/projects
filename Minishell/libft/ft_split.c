/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 23:25:58 by gdilly            #+#    #+#             */
/*   Updated: 2021/08/09 23:25:59 by gdilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*skip(char *s, char c)
{
	while (s && *s == c)
		s++;
	return (s);
}

static int	count(char *s, char c)
{
	int	result;

	s = skip(s, c);
	result = 0;
	while (s && *s)
	{
		result++;
		s = ft_strchr(s, c);
		s = skip(s, c);
	}
	return (result);
}

static int	selfdestruct(char **tab)
{
	int	i;

	if (!tab)
		return (1);
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	*ss;
	int		row;
	char	*temp;
	int		i;
	char	**tab;

	ss = (char *)s;
	row = count(ss, c);
	tab = malloc(sizeof(char *) * (row + 1));
	if (!tab)
		return (0);
	i = 0;
	while (i < row)
	{
		ss = skip(ss, c);
		temp = ft_strchr(ss, c);
		tab[i] = ft_substr(ss, 0, (unsigned int)(temp - ss));
		if (!tab[i++] && selfdestruct(tab))
			return (0);
		ss = temp;
	}
	tab[i] = 0;
	return (tab);
}
