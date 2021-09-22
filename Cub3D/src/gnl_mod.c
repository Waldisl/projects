/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_mod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msunspot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 21:56:38 by msunspot          #+#    #+#             */
/*   Updated: 2021/04/23 03:17:29 by msunspot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int		ft_error(int k, char **buf, char **line)
{
	if (k == -1)
		return (-1);
	free(*buf);
	*buf = NULL;
	if (*line == NULL)
	{
		*line = malloc(sizeof(char) * 1);
		*line[0] = 0;
	}
	return (0);
}

static int		ft_buf_free(char **buf, t_all *all)
{
	if (all->d.flag_er == 1 && *buf)
	{
		free(*buf);
		return (1);
	}
	return (0);
}

int				gnl_mod(int fd, char **line, t_all *all)
{
	static char	*buf = NULL;
	int			k;

	if (ft_buf_free(&buf, all) == 1)
		return (0);
	if (fd < 0 || BUF_SIZE <= 0 || !line)
		return (-1);
	*line = NULL;
	k = 1;
	if (buf)
		k = ft_line_copy(line, &buf);
	if (k == 0)
		return (1);
	if (!buf)
		if (!(buf = malloc(sizeof(char) * BUF_SIZE + 1)))
			return (-1);
	while ((k = read(fd, buf, BUF_SIZE)) > 0)
	{
		buf[k] = '\0';
		if (!ft_line_copy(line, &buf))
			return (1);
	}
	if (k <= 0)
		return (ft_error(k, &buf, line));
	return (1);
}
