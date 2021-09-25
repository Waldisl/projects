
#include "../cub3d.h"

void	ft_inc_ray(t_all *all)
{
	while (all->ray.hit == 0)
	{
		if (all->ray.sidedistx < all->ray.sidedisty)
		{
			all->ray.sidedistx += all->ray.deltadistx;
			all->ray.mapx += all->ray.stepx;
			all->ray.side = 0;
		}
		else
		{
			all->ray.sidedisty += all->ray.deltadisty;
			all->ray.mapy += all->ray.stepy;
			all->ray.side = 1;
		}
		if (all->d.map[all->ray.mapx][all->ray.mapy] == '1')
			all->ray.hit = 1;
	}
	ft_draw_start_end(all);
}

void	ft_draw_start_end(t_all *all)
{
	if (all->ray.side == 0)
		all->ray.perpwalldist = ((double)all->ray.mapx - \
				all->ray.posx + (1 - (double)all->ray.
				stepx) / 2) / all->ray.raydirx;
	else
		all->ray.perpwalldist = ((double)all->ray.mapy - \
				all->ray.posy + (1 - (double)all->ray.
				stepy) / 2) / all->ray.raydiry;
	all->ray.lineheight = (int)(all->d.ry / all->ray.perpwalldist);
	all->ray.drawstart = -all->ray.lineheight / 2 + all->d.ry / 2;
	if (all->ray.drawstart < 0)
		all->ray.drawstart = 0;
	all->ray.drawend = all->ray.lineheight / 2 + all->d.ry / 2;
	if (all->ray.drawend >= all->d.ry || all->ray.drawend < 0)
		all->ray.drawend = all->d.ry - 1;
}

void	ft_step_dist_side(t_all *all)
{
	if (all->ray.raydirx < 0)
	{
		all->ray.stepx = -1;
		all->ray.sidedistx = (all->ray.posx - all->ray.mapx) \
							* all->ray.deltadistx;
	}
	else
	{
		all->ray.stepx = 1;
		all->ray.sidedistx = (all->ray.mapx + 1 - all->ray.posx) \
							* all->ray.deltadistx;
	}
	if (all->ray.raydiry < 0)
	{
		all->ray.stepy = -1;
		all->ray.sidedisty = (all->ray.posy - all->ray.mapy) \
							* all->ray.deltadisty;
	}
	else
	{
		all->ray.stepy = 1;
		all->ray.sidedisty = (all->ray.mapy + 1 - all->ray.posy) \
							* all->ray.deltadisty;
	}
	ft_inc_ray(all);
}

void	ft_text_draw(t_all *all, int x, int y)
{
	y = all->ray.drawstart - 1;
	ft_initdata_texture(all);
	all->t.step = 1.0 * all->texture[0].height / all->ray.lineheight;
	all->t.texx = (int)(all->t.wallx * (double)all->texture
			[all->t.texdir].width);
	if (all->ray.side == 0 && all->ray.raydirx > 0)
		all->t.texx = all->texture[all->t.texdir].width -
			all->t.texx - 1;
	if (all->ray.side == 1 && all->ray.raydiry < 0)
		all->t.texx = all->texture[all->t.texdir].width -
			all->t.texx - 1;
	all->t.texpos = (all->ray.drawstart - all->d.ry / 2 +
			all->ray.lineheight / 2) * all->t.step;
	while (++y <= all->ray.drawend)
	{
		all->t.texy = (int)all->t.texpos &
			(all->texture[all->t.texdir].height - 1);
		all->t.texpos += all->t.step;
		if (y < all->d.ry && x < all->d.rx)
			all->mlxdata.addr[y * all->mlxdata.sizeline / 4 + x] =
				all->texture[all->t.texdir].addr[all->t.texy *
					all->texture[all->t.texdir].sizeline /
					4 + all->t.texx];
	}
}

int		ft_color_vertical(t_all *all)
{
	int j;

	j = -1;
	all->ray.drawend = all->d.ry - all->ray.drawstart;
	while (++j < all->ray.drawstart)
		all->mlxdata.addr[j * all->mlxdata.sizeline / 4 +
			all->ray.x] = all->d.c;
	if (j <= all->ray.drawend)
		ft_text_draw(all, all->ray.x, j);
	j = all->ray.drawend;
	while (++j < all->d.ry)
		all->mlxdata.addr[j * all->mlxdata.sizeline / 4 +
			all->ray.x] = all->d.f;
	return (0);
}
