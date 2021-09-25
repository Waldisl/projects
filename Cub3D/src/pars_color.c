
#include "../cub3d.h"

static	int	ft_check_char(char *str)
{
	int i;

	i = 1;
	if (str[1] == '\0')
		return (1);
	while (str[i] != '\0')
	{
		if ((str[i] < '0' || str[i] > '9') && str[i] != ' ' && str[i] != ','
		&& str[i] != '\n')
			return (1);
		i++;
	}
	return (0);
}

void		ft_atoi_er(char *str, t_all *all, int g, int i)
{
	while (str[i] != ',')
		i++;
	if (str[i] == ',')
		g = 1;
	i++;
	while (str[i] == ' ')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	while ((str[i] < '0' || str[i] > '9') && str[i])
	{
		if (str[i] == ',')
			g++;
		i++;
	}
	if (g != 2)
		all->d.flag_er = 1;
	if (ft_com(str) != 2)
		all->d.flag_er = 1;
}

int			ft_atoi_mod_res(char *str, t_all *all)
{
	int	s;

	s = 0;
	while (str[all->d.i] == ' ' || str[all->d.i] == '\t'
			|| str[all->d.i] == ',' || str[all->d.i] == '\n'
			|| str[all->d.i] == '\r' || str[all->d.i] == '\v'
			|| str[all->d.i] == '\f')
		all->d.i++;
	if (str[all->d.i] == '-' || str[all->d.i] == '+')
		all->d.flag_er = 1;
	while (str[all->d.i] >= '0' && str[all->d.i] <= '9')
	{
		if (s > 21474636)
			break ;
		s = (s * 10) + (str[all->d.i] - 48);
		all->d.i++;
	}
	while (str[all->d.i] >= '0' && str[all->d.i] <= '9')
		all->d.i++;
	all->d.flag_er = ft_check_char(str);
	if (str[1] != ' ' || ft_find_char((char *)str, ',') == 1)
		all->d.flag_er = 1;
	return (s);
}

int			ft_atoi_mod_cf(char *str, t_all *all)
{
	int	prov;

	if (str[1] != ' ')
		all->d.flag_er = 1;
	if ((all->d.flag_er = ft_check_char(str)) == 0)
		ft_atoi_er(str, all, 0, 0);
	while (str[all->d.i] == ' ' || str[all->d.i] == '\t' || str[all->d.i]
			== ',' || str[all->d.i] == '\n' || str[all->d.i] == '\r'
			|| str[all->d.i] == '\v' || str[all->d.i] == '\f')
	{
		all->d.i++;
		prov = 0;
		if (str[all->d.i] >= '0' && str[all->d.i] <= '9')
			all->d.flag_fc++;
		while (str[all->d.i] >= '0' && str[all->d.i] <= '9')
		{
			prov = (prov * 10) + str[all->d.i] - 48;
			all->d.at3_sum = (all->d.at3_sum * 10) + (str[all->d.i] - 48);
			all->d.i++;
		}
		if (prov > 255 || prov < 0)
			all->d.flag_er = 1;
	}
	return (all->d.at3_sum);
}

void		ft_res_color_cf(char **str, t_all *all)
{
	int	i;

	i = 0;
	all->d.i = 1;
	if (all->d.sizeline > 0 && (all->d.no == NULL || all->d.so == NULL ||
				all->d.we == NULL || all->d.ea == NULL || all->d.sp == NULL))
		all->d.flag_er = 1;
	if ((all->d.no != NULL || all->d.so != NULL || all->d.we != NULL ||
				all->d.ea != NULL || all->d.sp != NULL) && (all->d.rx == 0
				|| all->d.ry == 0))
		all->d.flag_er = 1;
	if (*str[i] == 'R')
	{
		if (all->d.rx != 0 && all->d.ry != 0)
			all->d.flag_er = 1;
		all->d.rx = ft_atoi_mod_res(*str, all);
		all->d.ry = ft_atoi_mod_res(*str, all);
		if (ft_atoi_mod_res(*str, all) > 0 || all->d.rx == 0 || all->d.ry == 0)
			all->d.flag_er = 1;
	}
	else if (*str[i] == 'F')
		all->d.f = ft_atoi_mod_cf(*str, all);
	else if (*str[i] == 'C')
		all->d.c = ft_atoi_mod_cf(*str, all);
}
