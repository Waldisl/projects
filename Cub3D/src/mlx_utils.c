/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msunspot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 21:53:16 by msunspot          #+#    #+#             */
/*   Updated: 2021/04/23 03:08:52 by msunspot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int			ft_press_key(int keycode, t_all *all)
{
	if (keycode == 119)
		all->mlxdata.forward = 1;
	else if (keycode == 115)
		all->mlxdata.back = 1;
	else if (keycode == 97)
		all->mlxdata.left = 1;
	else if (keycode == 100)
		all->mlxdata.right = 1;
	else if (keycode == 65361)
		all->mlxdata.rotate_left = 1;
	else if (keycode == 65363)
		all->mlxdata.rotate_right = 1;
	else if (keycode == 65307)
		ft_printerr(all, "Ok\n");
	return (1);
}

int			ft_release_key(int keycode, t_all *all)
{
	if (keycode == 119)
		all->mlxdata.forward = 0;
	else if (keycode == 115)
		all->mlxdata.back = 0;
	else if (keycode == 97)
		all->mlxdata.left = 0;
	else if (keycode == 100)
		all->mlxdata.right = 0;
	else if (keycode == 65361)
		all->mlxdata.rotate_left = 0;
	else if (keycode == 65363)
		all->mlxdata.rotate_right = 0;
	return (1);
}

static void	ft_adress_texture(t_all *all)
{
	all->texture[0].addr = (int *)mlx_get_data_addr(all->texture[0].img,
			&all->texture[0].bpp,
			&all->texture[0].sizeline, &all->texture[0].end);
	all->texture[1].addr = (int *)mlx_get_data_addr(all->texture[1].img,
			&all->texture[1].bpp,
			&all->texture[1].sizeline, &all->texture[1].end);
	all->texture[2].addr = (int *)mlx_get_data_addr(all->texture[2].img,
			&all->texture[2].bpp,
			&all->texture[2].sizeline, &all->texture[2].end);
	all->texture[3].addr = (int *)mlx_get_data_addr(all->texture[3].img,
			&all->texture[3].bpp,
			&all->texture[3].sizeline, &all->texture[3].end);
	all->texture[4].addr = (int *)mlx_get_data_addr(all->texture[4].img,
			&all->texture[4].bpp,
			&all->texture[4].sizeline, &all->texture[4].end);
}

void		ft_read_texture(t_all *all)
{
	if (!(all->texture[0].img = mlx_xpm_file_to_image(all->mlxdata.mlx_yk,
					all->d.no, &(all->texture[0].width),
					&(all->texture[0].height))))
		ft_printerr(all, "Read texture SO\n");
	if (!(all->texture[1].img = mlx_xpm_file_to_image(all->mlxdata.mlx_yk,
					all->d.so, &(all->texture[1].width),
					&(all->texture[1].height))))
		ft_printerr(all, "Read texture NO\n");
	if (!(all->texture[2].img = mlx_xpm_file_to_image(all->mlxdata.mlx_yk,
					all->d.we, &(all->texture[2].width),
					&(all->texture[2].height))))
		ft_printerr(all, "Read texture EA\n");
	if (!(all->texture[3].img = mlx_xpm_file_to_image(all->mlxdata.mlx_yk,
					all->d.ea, &(all->texture[3].width),
					&(all->texture[3].height))))
		ft_printerr(all, "Read texture WE\n");
	if (!(all->texture[4].img = mlx_xpm_file_to_image(all->mlxdata.mlx_yk,
					all->d.sp, &(all->texture[4].width),
					&(all->texture[4].height))))
		ft_printerr(all, "Read texture S\n");
	ft_adress_texture(all);
}
