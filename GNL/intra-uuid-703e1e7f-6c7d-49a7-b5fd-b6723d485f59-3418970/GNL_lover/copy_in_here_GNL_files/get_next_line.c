/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcrista <kcrista@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 19:31:34 by kcrista           #+#    #+#             */
/*   Updated: 2021/01/17 15:45:25 by kcrista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char			*chk_rmnd(char **rmnd, char ***line)
{
	char		*p_n;

	p_n = NULL;
	if (*rmnd)
	{
		if ((p_n = ft_strchr(*rmnd, '\n')))
		{
			*p_n = '\0';
			**line = ft_strdup(*rmnd);
			p_n = ft_strcpy(*rmnd, ++p_n);
		}
		else
		{
			**line = ft_strdup(*rmnd);
			free(*rmnd);
			*rmnd = NULL;
		}
	}
	else
		**line = ft_strdup("");
	return (p_n);
}

int				get_next_line(int fd, char **line)
{
	char		buf[BUFFER_SIZE + 1];
	static char *rmnd;
	int			text_buf;
	char		*p_n;
	char		*tmp;

	text_buf = 1;
	if (fd < 0 || BUFFER_SIZE <= 0 || !line || read(fd, NULL, 0) < 0)
		return (-1);
	p_n = chk_rmnd(&rmnd, &line);
	while (!p_n && (text_buf = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[text_buf] = '\0';
		tmp = *line;
		if ((p_n = ft_strchr(buf, '\n')))
		{
			*p_n = '\0';
			rmnd = ft_strdup(++p_n);
		}
		*line = ft_strjoin(*line, buf);
		free(tmp);
	}
	return ((!p_n && (text_buf == 0)) ? 0 : 1);
}
