
#include "../cub3d.h"

static void	ft_initdata_more(t_all *all)
{
	all->d.player_check = 0;
	all->d.empline = 0;
	all->d.flag_inmap = 0;
	all->d.at3_sum = 0;
	all->d.er_map = 0;
	all->d.player = 'g';
	all->d.flag_fc = 0;
	all->mlxdata.img = NULL;
	all->texture[0].img = NULL;
	all->texture[1].img = NULL;
	all->texture[2].img = NULL;
	all->texture[3].img = NULL;
	all->texture[4].img = NULL;
	all->mlxdata.mlx_w = NULL;
	all->d.map = NULL;
	all->s.order = NULL;
	all->s.dist = NULL;
	all->s.zbuffer = NULL;
	all->xy = NULL;
}

void		ft_initdata(t_all *all)
{
	all->d.flag_er = 0;
	all->d.no = NULL;
	all->d.so = NULL;
	all->d.we = NULL;
	all->d.ea = NULL;
	all->d.sp = NULL;
	all->d.f = -1;
	all->d.c = -1;
	all->d.rx = 0;
	all->d.ry = 0;
	all->d.numline = 0;
	all->d.sizeline = 0;
	all->d.map = NULL;
	all->d.dx = 0;
	all->d.dy = 0;
	ft_initdata_more(all);
}

static void	ft_init_mlx_data_more(t_all *all)
{
	if (all->d.player == 'N')
		all->ray.dirx = -1;
	if (all->d.player == 'S')
		all->ray.dirx = 1;
	if (all->d.player == 'E')
		all->ray.diry = 1;
	if (all->d.player == 'W')
		all->ray.diry = -1;
	if (all->d.player == 'N')
		all->ray.plany = 0.66;
	if (all->d.player == 'S')
		all->ray.plany = -0.66;
	if (all->d.player == 'E')
		all->ray.planx = 0.66;
	if (all->d.player == 'W')
		all->ray.planx = -0.66;
}

void		ft_init_mlx_data(t_all *all)
{
	if (!(all->s.zbuffer = (double *)malloc(sizeof(double) * all->d.rx)))
		exit(0);
	all->mlxdata.forward = 0;
	all->mlxdata.back = 0;
	all->mlxdata.left = 0;
	all->mlxdata.right = 0;
	all->mlxdata.rotate_right = 0;
	all->mlxdata.rotate_left = 0;
	all->ray.posx = (double)all->d.dx + 0.5;
	all->ray.posy = (double)all->d.dy + 0.5;
	all->ray.dirx = 0;
	all->ray.diry = 0;
	all->ray.planx = 0;
	all->ray.plany = 0;
	ft_init_mlx_data_more(all);
}
