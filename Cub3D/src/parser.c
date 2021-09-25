
#include "../cub3d.h"

void		ft_num_sprite_more(t_all *all, int i, int g, int v)
{
	while (++i < all->d.numline)
	{
		g = -1;
		while (++g < all->d.sizeline)
		{
			if (all->d.map[i][g] == '2')
			{
				all->xy[v].x = (double)i + 0.5;
				all->xy[v].y = (double)g + 0.5;
				v++;
			}
		}
	}
}

void		ft_num_sprite(t_all *all, int i)
{
	int j;

	all->s.spritenum = 0;
	ft_possible_errors(all);
	while (++i < all->d.numline)
	{
		j = -1;
		while (++j < all->d.sizeline)
		{
			if (all->d.map[i][j] == '2')
				all->s.spritenum += 1;
		}
	}
	if (!(all->xy = (t_sxy *)malloc(sizeof(t_sxy) * all->s.spritenum)))
		ft_printerr(all, "Malloc sprite xy failed");
	if (!(all->s.order = (int *)malloc(sizeof(int) * all->s.spritenum)))
		ft_printerr(all, "Malloc sprite order failed");
	if (!(all->s.dist = (double *)malloc(sizeof(double) * all->s.spritenum)))
		ft_printerr(all, "Malloc sprite dist failed");
	ft_num_sprite_more(all, -1, 0, 0);
	ft_mlx_init(all);
}

int			ft_map_in_struct(char *filemap, t_all *all, int k)
{
	int			fd;
	int			i;
	char		*str;

	i = 0;
	str = NULL;
	fd = open(filemap, O_RDONLY);
	if (!(all->d.map = malloc(sizeof(char*) * all->d.numline)))
		return (0);
	while (k != 0)
	{
		k = gnl_mod(fd, &str, all);
		if (all->d.flag_inmap == 1 && ft_empline(str, 0) == 0 &&
			i < all->d.numline)
			all->d.empline = 1;
		if ((all->d.flag_inmap = ft_valid_map(str, all)) == 1)
		{
			i++;
			ft_cp_map(str, all, 0);
		}
		free(str);
	}
	close(fd);
	ft_num_sprite(all, -1);
	return (0);
}

void		ft_pars(char *filemap, t_all *all)
{
	int			fd;
	int			k;
	char		*str;

	k = 1;
	str = NULL;
	if ((fd = open(filemap, O_DIRECTORY)) != -1)
		ft_printerr(all, "This is a directory\n");
	if ((fd = open(filemap, O_RDONLY)) == -1)
		ft_printerr(all, "File is incorrectly named\n");
	while (k != 0)
	{
		k = gnl_mod(fd, &str, all);
		if (all->d.flag_er == 1)
			ft_printerr(all, "Parsing a map \n");
		ft_res_color_cf(&str, all);
		ft_pars_texturs(str, all);
		ft_map_size_num(str, all, 0);
		free(str);
	}
	close(fd);
	if (all->d.sizeline == 0 || all->d.numline == 0)
		ft_printerr(all, "Map missing\n");
	ft_map_in_struct(filemap, all, 1);
}
