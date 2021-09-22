/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msunspot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 16:38:00 by msunspot          #+#    #+#             */
/*   Updated: 2020/12/22 16:38:00 by msunspot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		rez_gnl(char **line, char **rem_line, int r)
{
	char		*tmp;

	if (r > 0)
	{
		*line = ft_substr(*rem_line, 0, ft_strchr(*rem_line, '\n') - *rem_line);
		tmp = ft_strdup(*rem_line + (ft_strlen(*line) + 1));
		if (tmp == NULL)
			return (-1);
		ft_mdel((void **)rem_line);
		*rem_line = tmp;
		return (1);
	}
	if (r == 0)
	{
		*line = ft_strdup(*rem_line);
		if (*line == NULL)
			return (-1);
		ft_mdel((void **)rem_line);
		return (0);
	}
	return (-1);
}

int		get_next_line(int fd, char **line)
{
	int			r;
	char		buf[BUFFER_SIZE + (r = 1)];
	static char	*rem_line;
	char		*tmp;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	rem_line == NULL ? rem_line = ft_strnew(0) : NULL;
	while (!ft_strchr(rem_line, '\n') && (r = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[r] = '\0';
		tmp = ft_strjoin(rem_line, buf);
		if (tmp == NULL)
			return (-1);
		ft_mdel((void **)&rem_line);
		rem_line = tmp;
	}
	return (rez_gnl(line, &rem_line, r));
}

int		ft_mdel(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*g;
	size_t	i;

	if (!s)
		return (NULL);
	if ((size_t)start > ft_strlen(s))
		return (NULL);
	g = malloc(sizeof(char) * (len + 1));
	i = 0;
	if (!g)
		return (NULL);
	while (i < len)
	{
		g[i] = s[start + i];
		i++;
	}
	g[i] = '\0';
	return (g);
}

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
