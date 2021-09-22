/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_more.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msunspot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 19:40:46 by msunspot          #+#    #+#             */
/*   Updated: 2021/04/22 23:31:29 by msunspot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_init_ray_more(t_all *all)
{
	if (all->ray.raydiry == 0)
		all->ray.deltadistx = 0;
	else if (all->ray.raydirx == 0)
		all->ray.deltadistx = 1;
	else
		all->ray.deltadistx = sqrt(1 + (all->ray.raydiry
			* all->ray.raydiry) / (all->ray.raydirx *
			all->ray.raydirx));
	if (all->ray.raydirx == 0)
		all->ray.deltadisty = 0;
	else if (all->ray.raydiry == 0)
		all->ray.deltadisty = 1;
	else
		all->ray.deltadisty = sqrt(1 + (all->ray.raydirx *
			all->ray.raydirx) / (all->ray.raydiry *
			all->ray.raydiry));
}

void	ft_initdata_ray(t_all *all)
{
	all->ray.hit = 0;
	all->ray.perpwalldist = 0;
	all->ray.camerax = 2 * all->ray.x / (double)all->d.rx - 1;
	all->ray.raydirx = all->ray.dirx + all->ray.planx * \
						all->ray.camerax;
	all->ray.raydiry = all->ray.diry + all->ray.plany * \
						all->ray.camerax;
	all->ray.mapx = (int)all->ray.posx;
	all->ray.mapy = (int)all->ray.posy;
	all->ray.movespeed = 0.1;
	all->ray.rotspeed = 0.033 * 3.8;
	ft_init_ray_more(all);
}

void	ft_initdata_texture(t_all *all)
{
	if (all->ray.side == 0 && all->ray.raydirx < 0)
		all->t.texdir = 0;
	if (all->ray.side == 0 && all->ray.raydirx >= 0)
		all->t.texdir = 1;
	if (all->ray.side == 1 && all->ray.raydiry < 0)
		all->t.texdir = 2;
	if (all->ray.side == 1 && all->ray.raydiry >= 0)
		all->t.texdir = 3;
	if (all->ray.side == 0)
		all->t.wallx = all->ray.posy + all->ray.perpwalldist \
						* all->ray.raydiry;
	else
		all->t.wallx = all->ray.posx + all->ray.perpwalldist \
						* all->ray.raydirx;
	all->t.wallx -= floor((all->t.wallx));
}
