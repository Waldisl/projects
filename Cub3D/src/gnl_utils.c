/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msunspot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 21:59:26 by msunspot          #+#    #+#             */
/*   Updated: 2021/04/23 03:08:13 by msunspot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*g;
	size_t	i;

	i = 0;
	g = malloc(sizeof(char) * (len + 1));
	if (start < (unsigned int)ft_strlen((char *)s))
	{
		while (s[start] != '\0' && i < len)
		{
			g[i] = s[start];
			i++;
			start++;
		}
	}
	g[i] = '\0';
	return (g);
}

char		*ft_strjoin(char *s1, char *s2)
{
	char	*g;
	int		i;
	int		j;

	if (!(g = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		g[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		g[i] = s2[j];
		j++;
		i++;
	}
	g[i] = '\0';
	return (g);
}

static char	*ft_sub_b(char *buf, unsigned int start, int len)
{
	int		i;
	char	*g;

	g = NULL;
	g = ft_strjoin(g, buf);
	i = 0;
	while (g[i] != '\0' && i < len)
	{
		buf[i] = g[start];
		i++;
		start++;
	}
	buf[i] = 0;
	free(g);
	return (buf);
}

static int	ft_strlen_n(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int			ft_line_copy(char **line, char **buf)
{
	int		len;
	char	*tmp;
	char	*tmp_line;

	if ((len = ft_strlen_n(*buf)) >= 0)
	{
		tmp = ft_substr(*buf, 0, len);
		tmp_line = *line;
		*line = ft_strjoin(*line, tmp);
		free(tmp);
		free(tmp_line);
		*buf = ft_sub_b(*buf, len + 1, (ft_strlen(*buf) - len));
		return (0);
	}
	else
	{
		tmp = NULL;
		if (*line)
			tmp = *line;
		*line = ft_strjoin(*line, *buf);
		if (tmp)
			free(tmp);
		return (1);
	}
	return (-1);
}
