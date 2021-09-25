/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msunspot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 22:51:48 by msunspot          #+#    #+#             */
/*   Updated: 2021/08/10 22:51:49 by msunspot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	ft_check_dir(char *tmp, char *pwd, char **av)
{
	struct stat	buf;
	int			flag;
	char		*pwd_dop;

	if (chdir(tmp) == -1)
	{
		chdir(pwd);
		flag = stat(*av, &buf);
		if (flag == -1)
			ft_print_err_2("cd", av[0], "No such file or directory", 1);
		else if (flag == 0)
			ft_print_error_1("cd", "Not a directory", 1);
		return (1);
	}
	pwd_dop = ft_get_path_pwd();
	ft_overwrite_env("PWD", pwd_dop);
	ft_overwrite_env("OLDPWD", pwd);
	free(pwd_dop);
	return (0);
}

static void	ft_go_dir(char *env_name, char **av)
{
	char	*pwd;
	char	*env;

	pwd = ft_get_path_pwd();
	env = ft_find_env(env_name);
	ft_check_dir(env, pwd, av);
	free(pwd);
	free(env);
}

static bool	ft_check_args_count(char **av)
{
	char	*pwd;

	if (!ft_dop_check_av(av))
		return (false);
	else if (ft_len_arr(av) == 1)
	{
		pwd = ft_get_path_pwd();
		if (ft_find_char(av[0], '/') == ft_strlen(av[0]))
		{
			ft_check_dir("/", pwd, av);
			free(pwd);
			return (false);
		}
		if (ft_strcompare(av[0], "-"))
		{
			ft_go_dir("OLDPWD", av);
			printf("%s\n", pwd);
			free(pwd);
			return (false);
		}
		free(pwd);
	}
	return (true);
}

static void	ft_get_backslash(char **str, char *prefix)
{
	char	*tmp;

	tmp = ft_strdup(prefix);
	ft_add_str(&tmp, *str);
	free(*str);
	*str = tmp;
}

void	ft_cmds_cd(char **argv)
{
	int		i;
	char	*pwd;
	char	**parts_pwd;

	argv++;
	i = -1;
	if (!ft_check_args_count(argv))
		return ;
	parts_pwd = ft_split(*argv, '/');
	if (!parts_pwd || ft_len_arr(parts_pwd) == 0)
		ft_go_dir("HOME", argv);
	pwd = ft_get_path_pwd();
	while (parts_pwd[++i])
	{
		if (i == 0 && argv[0][0] == '/')
			ft_get_backslash(&parts_pwd[i], "/");
		if (ft_check_dir(parts_pwd[i], pwd, argv))
			break ;
		else
			g_global.code = 0;
	}
	free(pwd);
	ft_arr_free(parts_pwd);
}
