
#include "../cub3d.h"

static void	ft_distantion_order_more(t_all *all)
{
	int i;

	i = -1;
	while (++i < all->s.spritenum)
	{
		all->s.order[i] = i;
		all->s.dist[i] = ((all->ray.posx - all->xy[i].x) *
				(all->ray.posx - all->xy[i].x) + (all->ray.posy -
					all->xy[i].y) * (all->ray.posy - all->xy[i].y));
	}
}

static void	ft_distantion_order(t_all *all)
{
	int		i;
	int		g;
	double	temp;

	ft_distantion_order_more(all);
	i = -1;
	while (++i < all->s.spritenum)
	{
		g = -1;
		while (++g < all->s.spritenum - 1)
		{
			if (all->s.dist[g] < all->s.dist[g + 1])
			{
				temp = all->s.dist[g];
				all->s.dist[g] = all->s.dist[g + 1];
				all->s.dist[g + 1] = temp;
				temp = all->s.order[g];
				all->s.order[g] = all->s.order[g + 1];
				all->s.order[g + 1] = (int)temp;
			}
		}
	}
}

static void	ft_calc(t_all *all, int i)
{
	all->s.spritex = all->xy[all->s.order[i]].x - all->ray.posx;
	all->s.spritey = all->xy[all->s.order[i]].y - all->ray.posy;
	all->s.invdet = 1 / (all->ray.planx * all->ray.diry -
			all->ray.dirx * all->ray.plany);
	all->s.transformx = all->s.invdet * (all->ray.diry *
			all->s.spritex - all->ray.dirx * all->s.spritey);
	all->s.transformy = all->s.invdet * (-all->ray.plany *
			all->s.spritex + all->ray.planx * all->s.spritey);
	all->s.spritescreenx = (int)((all->d.rx / 2) * (1 + all->s.transformx
				/ all->s.transformy));
	all->s.spriteheight = abs((int)(all->d.ry / (all->s.transformy)));
	all->s.drawstarty = -all->s.spriteheight / 2 + all->d.ry / 2;
	if (all->s.drawstarty < 0)
		all->s.drawstarty = 0;
	all->s.drawendy = all->s.spriteheight / 2 + all->d.ry / 2;
	if (all->s.drawendy >= all->d.ry)
		all->s.drawendy = all->d.ry;
	all->s.spritewidth = abs((int)(all->d.ry / (all->s.transformy)));
	all->s.drawstartx = -all->s.spritewidth / 2 + all->s.spritescreenx;
	if (all->s.drawstartx < 0)
		all->s.drawstartx = 0;
	all->s.drawendx = all->s.spritewidth / 2 + all->s.spritescreenx;
	if (all->s.drawendx >= all->d.rx)
		all->s.drawendx = all->d.rx;
}

static void	ft_sprite_draw(t_all *all, int y, int tx, int poloc)
{
	int		d;
	int		ty;

	while (y < all->s.drawendy)
	{
		d = (y) * 256 - all->d.ry * 128 + all->s.spriteheight * 128;
		ty = ((d * all->texture[4].height) / all->s.spriteheight) / 256;
		if (all->texture[4].addr[ty * all->texture[4].sizeline / 4 +
				tx] != -16777216)
		{
			all->mlxdata.addr[y * all->mlxdata.sizeline / 4 + poloc] =
				all->texture[4].addr[ty * all->texture[4].sizeline /
				4 + tx];
		}
		y++;
	}
}

void		ft_spr(t_all *all)
{
	int i;
	int y;
	int poloc;
	int tx;

	i = -1;
	ft_distantion_order(all);
	while (++i < all->s.spritenum)
	{
		ft_calc(all, i);
		poloc = all->s.drawstartx;
		while (poloc < all->s.drawendx)
		{
			tx = (int)(256 * (poloc - (-all->s.spritewidth / 2 +
							all->s.spritescreenx)) * all->texture[4].width
					/ all->s.spritewidth) / 256;
			if (all->s.transformy > 0 && poloc >= 0 && poloc < all->d.rx
					&& all->s.transformy < all->s.zbuffer[poloc])
			{
				y = all->s.drawstarty;
				ft_sprite_draw(all, y, tx, poloc);
			}
			poloc++;
		}
	}
}
