
#include "../../includes/minishell.h"

char	**ft_get_paths(void)
{
	char	*path;
	char	**paths;

	path = ft_find_env("PATH");
	paths = ft_split(path, ':');
	free(path);
	return (paths);
}

bool	ft_str_isdigit(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
	}
	return (true);
}

bool	ft_dop_check_av(char **argv)
{
	if (ft_len_arr(argv) > 1)
	{
		ft_print_error_1("cd", "too many arguments", 1);
		return (false);
	}
	return (true);
}
