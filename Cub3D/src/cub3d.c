/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msunspot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 21:09:23 by msunspot          #+#    #+#             */
/*   Updated: 2021/04/22 23:16:15 by msunspot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		ft_cub3d(char *str, t_all *all)
{
	int	i;

	i = ft_strlen(str);
	if (str[i - 4] == '.' && str[i - 3] == 'c' && str[i - 2] == 'u' &&
		str[i - 1] == 'b')
		ft_pars(str, all);
	else
		ft_printerr(all, "Invalid map name (*.cub)\n");
	return (0);
}

int		main(int argc, char **argv)
{
	t_all all;

	ft_initdata(&all);
	if (argc == 2 || (argc == 3 && ft_saveflag(argv[2]) == 1))
	{
		if (argc == 3)
			all.d.save = 1;
		ft_cub3d(argv[1], &all);
	}
	else
		write(1, "Error\nInvalid arguments\n", 24);
}
