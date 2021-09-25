/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 23:42:56 by gdilly            #+#    #+#             */
/*   Updated: 2021/08/09 23:42:57 by gdilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_add_char(char **str, char c)
{
	char	*tmp_1;
	char	*tmp_2;

	tmp_2 = ft_calloc(sizeof(char), 2);
	tmp_2[0] = c;
	tmp_1 = ft_strjoin(*str, tmp_2);
	free(*str);
	free(tmp_2);
	*str = tmp_1;
}

int	ft_len_arr(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (0);
	while (array[i])
		i++;
	return (i);
}

bool	ft_strcompare(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (false);
	while (*s1 == *s2 && *s1)
	{
		s1++;
		s2++;
	}
	return (*s1 == *s2);
}

void	ft_add_str(char **str, char *new_value)
{
	char	*tmp;

	tmp = ft_strjoin(*str, new_value);
	free(*str);
	*str = tmp;
}

char	*ft_find_env(char *str)
{
	char	*name;
	char	*data;
	int		i;
	int		j;

	i = -1;
	while (g_global.env[++i])
	{
		j = 0;
		while (g_global.env[i][j] != '=')
			j++;
		name = ft_calloc(sizeof(char), j + 1);
		data = ft_calloc(1, ft_strlen(g_global.env[i]) - j + 1);
		ft_strlcpy(name, g_global.env[i], j + 1);
		ft_strlcpy(data, g_global.env[i] + j + 1,
			ft_strlen(g_global.env[i]) - j);
		if (ft_strcompare(str, name))
		{
			free(name);
			return (data);
		}
		free(name);
		free(data);
	}
	return (0);
}
