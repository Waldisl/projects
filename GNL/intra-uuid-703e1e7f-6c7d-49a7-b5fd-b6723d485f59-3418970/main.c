/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msunspot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 16:44:00 by msunspot          #+#    #+#             */
/*   Updated: 2020/12/22 16:44:00 by msunspot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	char	*line;
	int		fd;
	int		i;

	fd = open("test.txt", O_RDONLY);
	while ((i = get_next_line(fd, &line)) >= 0)
	{
		printf("%s\n", line);
		free(line);
		if (i == 0)
			break ;
	}
	close(fd);
	return (0);
}
