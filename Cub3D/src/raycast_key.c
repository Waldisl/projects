
#include "../cub3d.h"

void	ft_key_w_key_s(t_all *all)
{
	if (all->mlxdata.forward == 1)
	{
		if (all->d.map[(int)(all->ray.posx + (all->ray.dirx * all->
						ray.movespeed * 2))][(int)all->ray.posy] == '0')
			all->ray.posx += all->ray.dirx * all->ray.movespeed;
		if (all->d.map[(int)(all->ray.posx)][(int)(all->ray.posy +
					(all->ray.diry * all->ray.movespeed * 2))] == '0')
			all->ray.posy += all->ray.diry * all->ray.movespeed;
	}
	if (all->mlxdata.back == 1)
	{
		if (all->d.map[(int)(all->ray.posx - (all->ray.dirx * all->
						ray.movespeed * 2))][(int)(all->ray.posy)] == '0')
			all->ray.posx -= all->ray.dirx * all->ray.movespeed;
		if (all->d.map[(int)(all->ray.posx)][(int)(all->ray.posy -
					(all->ray.diry * all->ray.movespeed * 2))] == '0')
			all->ray.posy -= all->ray.diry * all->ray.movespeed;
	}
}

void	ft_key_a_key_d(t_all *all)
{
	if (all->mlxdata.right == 1)
	{
		if (all->d.map[(int)(all->ray.posx + all->ray.diry *
					(all->ray.movespeed * 2))][(int)all->ray.posy] == '0')
			all->ray.posx += all->ray.diry * all->ray.movespeed;
		if (all->d.map[(int)all->ray.posx][(int)(all->ray.posy -
					all->ray.dirx *
					(all->ray.movespeed * 2))] == '0')
			all->ray.posy -= all->ray.dirx * all->ray.movespeed;
	}
	if (all->mlxdata.left == 1)
	{
		if (all->d.map[(int)(all->ray.posx - all->ray.diry *
					(all->ray.movespeed * 2))][(int)all->ray.posy] == '0')
			all->ray.posx -= all->ray.diry * all->ray.movespeed;
		if (all->d.map[(int)all->ray.posx][(int)(all->ray.posy +
					all->ray.dirx *
					(all->ray.movespeed * 2))] == '0')
			all->ray.posy += all->ray.dirx * all->ray.movespeed;
	}
}

void	ft_rot_left(t_all *all, double dirx)
{
	double planex;

	dirx = all->ray.dirx;
	planex = all->ray.planx;
	if (all->mlxdata.rotate_left == 1)
	{
		all->ray.dirx = all->ray.dirx * cos(all->ray.rotspeed / 2) -
			all->ray.diry * sin(all->ray.rotspeed / 2);
		all->ray.diry = dirx * sin(all->ray.rotspeed / 2) + all->
			ray.diry * cos(all->ray.rotspeed / 2);
		all->ray.planx = all->ray.planx * cos(all->ray.rotspeed / 2) -
			all->ray.plany * sin(all->ray.rotspeed / 2);
		all->ray.plany = planex * sin(all->ray.rotspeed / 2) +
			all->ray.plany * cos(all->ray.rotspeed / 2);
	}
}

void	ft_rot_left_rigth(t_all *all)
{
	double planx;
	double dirx;

	planx = all->ray.planx;
	dirx = all->ray.dirx;
	if (all->mlxdata.rotate_right == 1)
	{
		all->ray.dirx = all->ray.dirx * cos(-all->ray.rotspeed / 2) -
			all->ray.diry * sin(-all->ray.rotspeed / 2);
		all->ray.diry = dirx * sin(-all->ray.rotspeed / 2) +
			all->ray.diry * cos(-all->ray.rotspeed / 2);
		all->ray.planx = all->ray.planx * cos(-all->ray.rotspeed / 2)
			- all->ray.plany * sin(-all->ray.rotspeed / 2);
		all->ray.plany = planx * sin(-all->ray.rotspeed / 2) +
			all->ray.plany * cos(-all->ray.rotspeed / 2);
	}
	ft_rot_left(all, dirx);
}

void	ft_switch(t_all *all)
{
	void *tmp;

	tmp = all->mlxdata.img;
	all->mlxdata.img = all->mlxdata.img2;
	all->mlxdata.img2 = tmp;
	tmp = all->mlxdata.addr;
	all->mlxdata.addr = all->mlxdata.addr2;
	all->mlxdata.addr2 = tmp;
}
