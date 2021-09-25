
#include "../cub3d.h"

static int	ft_dot_str(char *str)
{
	int j;
	int i;

	j = 0;
	i = 0;
	while (str[i] != '.')
		i++;
	while (str[i] != '\0')
	{
		i++;
		j++;
	}
	return (j);
}

static int	ft_tex_path(char *str, char **texture, t_all *all, int j)
{
	int i;

	i = 0;
	if (*texture != NULL)
	{
		all->d.flag_er = 1;
		return (0);
	}
	if (ft_find_char(str, '.') == 0 || ft_find_char(str, '/') == 0
			|| ft_dot_str(str) <= 3)
		all->d.flag_er = 1;
	while (str[j] != '.')
	{
		if (str[j] != ' ')
			all->d.flag_er = 1;
		j++;
	}
	if (!(*texture = (char *)(malloc(sizeof(char) * (ft_dot_str(str) + 1)))))
		all->d.flag_er = 1;
	while (str[j] != '\0')
	{
		(*texture)[i++] = str[j++];
	}
	(*texture)[i] = '\0';
	return (0);
}

void		ft_pars_texturs(char *str, t_all *all)
{
	static int	g = 0;

	if (str[0] == 'S' && str[1] == 'O')
		ft_tex_path(str, &all->d.so, all, 2);
	else if (str[0] == 'N' && str[1] == 'O')
		ft_tex_path(str, &all->d.no, all, 2);
	else if (str[0] == 'E' && str[1] == 'A')
		ft_tex_path(str, &all->d.ea, all, 2);
	else if (str[0] == 'W' && str[1] == 'E')
		ft_tex_path(str, &all->d.we, all, 2);
	else if (str[0] == 'S' && str[1] != 'O')
		ft_tex_path(str, &all->d.sp, all, 1);
	else if (str[0] != 'N' && str[0] != 'S' && str[0] != 'W' && str[0] != 'E'
			&& str[0] != 'R' && str[0] != 'F' && str[0] != 'C'
			&& str[0] > 65 && str[0] < 122)
		all->d.flag_er = 1;
	if (str[0] == 'N' || str[0] == 'S' || str[0] == 'W' || str[0] == 'E' ||
		str[0] == 'R' || str[0] == 'F' || str[0] == 'C')
		g++;
	if (g > 8)
		all->d.flag_er = 1;
}
