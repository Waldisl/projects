/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_built_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 23:43:11 by gdilly            #+#    #+#             */
/*   Updated: 2021/08/09 23:43:12 by gdilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	ft_find_char(const char *str, char c)
{
	int	j;

	j = 0;
	while (*str)
	{
		if (*str == c)
			j++;
		str++;
	}
	return (j);
}

char	*ft_get_path_pwd(void)
{
	char	buffer[4096];

	if (getcwd(buffer, 4096) == 0)
		exit(EXIT_FAILURE);
	return (ft_strdup(buffer));
}

static int	ft_checkunset(char c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	else if (c == '_')
		return (1);
	return (0);
}

int	ft_check_unset(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_checkunset(str[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

void	ft_sort_tmp(char **tmp_1)
{
	char	*tmp;
	int		i;
	int		j;

	i = -1;
	while (g_global.env[++i])
		tmp_1[i] = ft_strdup(g_global.env[i]);
	i = 1;
	while (i < ft_len_arr(g_global.env))
	{
		j = 0;
		while (j < ft_len_arr(g_global.env) - i)
		{
			if ((ft_strncmp(tmp_1[j + 1], tmp_1[j], \
			ft_strlen(tmp_1[j + 1]) + ft_strlen(tmp_1[j]))) < 0)
			{
				tmp = tmp_1[j];
				tmp_1[j] = tmp_1[j + 1];
				tmp_1[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}
