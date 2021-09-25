
#include "../cub3d.h"

int		ft_valid_map(char *str, t_all *all)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	if (ft_find_char(str, '1') == 1 || ft_find_char(str, '0') == 1)
	{
		while (str[i] != '\0')
		{
			if (str[i] != ' ' && str[i] != '0' && str[i] != '1' \
					&& str[i] != '2' && str[i] != 'N' && str[i] != 'S' \
					&& str[i] != 'E' && str[i] != 'W' && str[i] != '\n'
					&& str[i] != '\t')
			{
				if (all->d.flag_inmap == 1)
					all->d.er_map = 2;
				return (0);
			}
			i++;
		}
		return (1);
	}
	return (0);
}

void	ft_map_size_num(char *str, t_all *all, int i)
{
	if (ft_valid_map(str, all) == 1)
	{
		if (all->d.f == -1 || all->d.c == -1 || all->d.no == NULL ||
				all->d.so == NULL || all->d.we == NULL ||
				all->d.ea == NULL || all->d.sp == NULL)
			all->d.flag_er = 1;
		if ((i = ft_strlen(str)) > all->d.sizeline)
			all->d.sizeline = i;
		all->d.numline = all->d.numline + 1;
	}
}
