/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msunspot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 22:20:59 by msunspot          #+#    #+#             */
/*   Updated: 2021/04/23 03:07:09 by msunspot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void		ft_possible_errors(t_all *all)
{
	if (ft_close_map(all, 0) == 1)
		ft_printerr(all, "Map is not closed\n");
	if (all->d.player == 'g')
		ft_printerr(all, "No player (N, S, W, E)\n");
	if (all->d.flag_fc != 6)
		ft_printerr(all, "Bad mlxdata FLOOR or CEILING\n");
	if (all->d.player_check == 1)
		ft_printerr(all, "More than one player on the map\n");
	if (all->d.empline == 1)
		ft_printerr(all, "Empty line on the map\n");
	if (all->d.er_map == 2)
		ft_printerr(all, "Bad character in the map\n");
}

static void	ft_printerr_more(t_all *all, char *str)
{
	if (all->d.map)
		free(all->d.map);
	if (all->s.order)
		free(all->s.order);
	if (all->s.dist)
		free(all->s.dist);
	if (all->xy)
		free(all->xy);
	if (all->s.zbuffer)
		free(all->s.zbuffer);
	ft_esc_exit(all, str);
}

void		ft_printerr(t_all *all, char *str)
{
	int i;

	i = -1;
	if (all->d.no)
		free(all->d.no);
	if (all->d.so)
		free(all->d.so);
	if (all->d.we)
		free(all->d.we);
	if (all->d.ea)
		free(all->d.ea);
	if (all->d.sp)
		free(all->d.sp);
	if (all->d.map)
	{
		while (++i < all->d.numline)
			free(all->d.map[i]);
	}
	ft_printerr_more(all, str);
}

int			ft_esc_exit(t_all *all, char *str)
{
	if (str[0] != 'O')
		write(1, "Error\n", 6);
	perror(str);
	if (all->mlxdata.img)
		mlx_destroy_image(all->mlxdata.mlx_yk, all->mlxdata.img);
	if (all->texture[0].img)
		mlx_destroy_image(all->mlxdata.mlx_yk, all->texture[0].img);
	if (all->texture[1].img)
		mlx_destroy_image(all->mlxdata.mlx_yk, all->texture[1].img);
	if (all->texture[2].img)
		mlx_destroy_image(all->mlxdata.mlx_yk, all->texture[2].img);
	if (all->texture[3].img)
		mlx_destroy_image(all->mlxdata.mlx_yk, all->texture[3].img);
	if (all->texture[4].img)
		mlx_destroy_image(all->mlxdata.mlx_yk, all->texture[4].img);
	if (all->mlxdata.mlx_w)
		mlx_destroy_window(all->mlxdata.mlx_yk, all->mlxdata.mlx_w);
	exit(0);
}
