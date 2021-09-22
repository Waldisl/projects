/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_more.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msunspot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 23:14:13 by msunspot          #+#    #+#             */
/*   Updated: 2021/04/23 03:22:19 by msunspot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		ft_saveflag(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (ft_strlen(str) < 7 && str[i - 6] == '-' && str[i - 5] == '-'
		&& str[i - 4] == 's' && str[i - 3] == 'a' && str[i - 2] == 'v'
		&& str[i - 1] == 'e')
		return (1);
	else
		return (0);
}

int		ft_com(const char *str)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == ',')
			j++;
	}
	return (j);
}

int		ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
			i++;
		return (i);
	}
	return (0);
}

int		ft_empline(char *str, int i)
{
	while (str[i])
	{
		if (str[i] != '\f' && str[i] != '\r' && str[i] != '\0' &&
				str[i] != '\n' && str[i] != ' ' && str[i] != '\v'
				&& str[i] != '\t')
			return (1);
		i++;
	}
	return (0);
}

int		ft_find_char(char *str, char c)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}
