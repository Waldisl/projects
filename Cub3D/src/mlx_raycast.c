
#include "../cub3d.h"

int		ft_raycast(t_all *all)
{
	all->ray.x = 0;
	while (all->ray.x < all->d.rx)
	{
		ft_initdata_ray(all);
		ft_step_dist_side(all);
		ft_color_vertical(all);
		all->s.zbuffer[all->ray.x] = all->ray.perpwalldist;
		all->ray.x++;
	}
	ft_spr(all);
	if (all->d.save == 1)
		ft_image_save(all);
	mlx_put_image_to_window(all->mlxdata.mlx_yk, all->mlxdata.mlx_w,
			all->mlxdata.img, 0, 0);
	ft_key_w_key_s(all);
	ft_key_a_key_d(all);
	ft_rot_left_rigth(all);
	ft_switch(all);
	return (0);
}

void	ft_mlx_rx_ry(t_all *all)
{
	mlx_get_screen_size(all->mlxdata.mlx_yk, &all->d.screenx, &all->d.screeny);
	if (all->d.rx > all->d.screenx)
		all->d.rx = all->d.screenx;
	if (all->d.ry > all->d.screeny)
		all->d.ry = all->d.screeny;
}

int		ft_mlx_init(t_all *all)
{
	ft_init_mlx_data(all);
	if (!(all->mlxdata.mlx_yk = mlx_init()))
		ft_printerr(all, "Mlx init not working \n");
	ft_mlx_rx_ry(all);
	ft_read_texture(all);
	all->mlxdata.img = mlx_new_image(all->mlxdata.mlx_yk, all->d.rx, all->d.ry);
	all->mlxdata.addr = (int *)mlx_get_data_addr(all->mlxdata.img,
			&all->mlxdata.bpp, &all->mlxdata.sizeline, &all->mlxdata.end);
	if (all->d.save == 1)
		ft_raycast(all);
	all->mlxdata.mlx_w = mlx_new_window(all->mlxdata.mlx_yk, all->d.rx,
			all->d.ry, "Msunspot Game");
	all->mlxdata.img2 = mlx_new_image(all->mlxdata.mlx_yk, all->d.rx,
						all->d.ry);
	all->mlxdata.addr2 = (int *)mlx_get_data_addr(all->mlxdata.img2, &all->
			mlxdata.bpp, &all->mlxdata.sizeline, &all->mlxdata.end);
	mlx_hook(all->mlxdata.mlx_w, 33, 1L << 17, ft_esc_exit, all);
	mlx_hook(all->mlxdata.mlx_w, 2, 1L << 0, ft_press_key, all);
	mlx_loop_hook(all->mlxdata.mlx_yk, ft_raycast, all);
	mlx_hook(all->mlxdata.mlx_w, 3, 1L << 1, ft_release_key, all);
	mlx_loop(all->mlxdata.mlx_yk);
	return (0);
}

void	ft_print_win(t_all *all, int fd)
{
	int	temp;

	write(fd, "BM", 2);
	temp = 14 + 40 + 4 * all->d.rx * all->d.ry;
	write(fd, &temp, 4);
	temp = 0;
	write(fd, &temp, 2);
	write(fd, &temp, 2);
	temp = 54;
	write(fd, &temp, 4);
	temp = 40;
	write(fd, &temp, 4);
	write(fd, &all->d.rx, 4);
	write(fd, &all->d.ry, 4);
	temp = 1;
	write(fd, &temp, 2);
	write(fd, &all->mlxdata.bpp, 2);
	temp = 0;
	write(fd, &temp, 4);
	write(fd, &temp, 4);
	write(fd, &temp, 4);
	write(fd, &temp, 4);
	write(fd, &temp, 4);
	write(fd, &temp, 4);
}

void	ft_image_save(t_all *all)
{
	int	fd;
	int	x;
	int	ry;

	ry = all->d.ry;
	if ((fd = open("./image.bmp", O_CREAT | O_RDWR)) == -1)
		ft_printerr(all, "Unable to create image.bmp\n");
	ft_print_win(all, fd);
	while (ry >= 0)
	{
		x = 0;
		while (x < all->d.rx)
		{
			write(fd, &all->mlxdata.addr[ry * all->mlxdata.sizeline / 4 + x],
				4);
			x++;
		}
		ry--;
	}
	system("chmod 777 image.bmp");
	ft_printerr(all, "Ok save\n");
}
