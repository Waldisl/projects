
#include "../cub3d.h"

int			ft_player(char c, t_all *all, int i, int j)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (all->d.player != 'g')
			all->d.player_check = 1;
		all->d.player = c;
		all->d.dx = i;
		all->d.dy = j;
		return (1);
	}
	return (0);
}

static int	ft_close_map_ver(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '1')
			return (1);
		i++;
	}
	return (0);
}

int			ft_close_map(t_all *all, int i)
{
	while (i < all->d.numline)
	{
		if (all->d.map[i][0] != '1')
			return (1);
		i++;
	}
	i = 0;
	while (i < all->d.numline)
	{
		if (all->d.map[i][all->d.sizeline - 1] != '1')
			return (1);
		i++;
	}
	if (ft_close_map_ver(all->d.map[0]) == 1)
		return (1);
	if (ft_close_map_ver(all->d.map[all->d.numline - 1]) == 1)
		return (1);
	return (0);
}

int			ft_cp_map(char *str, t_all *all, int g)
{
	static int	i = 0;

	all->d.map[i] = NULL;
	if (!(all->d.map[i] = malloc(sizeof(char) * all->d.sizeline + 1)))
		return (0);
	while (str[g] != '\0')
	{
		if (ft_player(str[g], all, i, g) == 1)
			all->d.map[i][g] = '0';
		else if (str[g] == ' ')
			all->d.map[i][g] = '1';
		else
			all->d.map[i][g] = str[g];
		g++;
	}
	while (g <= (all->d.sizeline - 1))
	{
		all->d.map[i][g] = '1';
		g++;
	}
	all->d.map[i++][g] = '\0';
	return (0);
}
