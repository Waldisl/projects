
#include "../../../includes/minishell.h"

static void	ft_print_var(void)
{
	int		i;
	char	*var_name;
	char	*var_content;
	int		i_tmp;
	char	**tmp_1;

	tmp_1 = ft_calloc(sizeof(char *), ft_len_arr(g_global.env) + 1);
	ft_sort_tmp(tmp_1);
	i = -1;
	while (tmp_1[++i])
	{
		i_tmp = 0;
		while (tmp_1[i][i_tmp] != '=')
			i_tmp++;
		var_name = ft_calloc(sizeof(char), i_tmp + 2);
		var_content = ft_calloc(sizeof(char),
				ft_strlen(tmp_1[i]) - i_tmp + 1);
		ft_strlcpy(var_name, tmp_1[i], i_tmp + 2);
		ft_strlcpy(var_content, tmp_1[i] + i_tmp + 1,
			ft_strlen(tmp_1[i]) - i_tmp);
		printf("declare -x %s\"%s\"\n", var_name, var_content);
		free(var_name);
		free(var_content);
	}
	ft_arr_free(tmp_1);
}

static void	ft_exec_change(int i_env, char **av, int arg, int i)
{
	char	**env;

	if (g_global.env[i_env] && ft_strncmp(g_global.env[i_env], av[arg], i) == 0)
	{
		free(g_global.env[i_env]);
		g_global.env[i_env] = ft_strdup(av[arg]);
	}
	else
	{
		i_env = ft_len_arr(g_global.env) + 1;
		env = ft_calloc(sizeof(char *), i_env + 1);
		i_env = 0;
		while (g_global.env[i_env])
		{
			env[i_env] = ft_strdup(g_global.env[i_env]);
			free(g_global.env[i_env]);
			i_env++;
		}
		env[i_env] = ft_strdup(av[arg]);
		free(g_global.env);
		g_global.env = env;
	}
}

static void	ft_init_var(t_exp *exp)
{
	exp->i = 0;
	exp->j = 0;
	exp->tmp = 0;
}

static int	ft_change_var(char **av)
{
	t_exp	exp;

	exp = (t_exp){0};
	while (++exp.ac < ft_len_arr(av))
	{
		if (av[exp.ac][exp.i] == 0)
			break ;
		ft_init_var(&exp);
		while (av[exp.ac][exp.i] && av[exp.ac][exp.i] != '=')
			ft_add_char(&exp.tmp, av[exp.ac][exp.i++]);
		if (av[exp.ac][exp.i] != '=')
			ft_add_char(&av[exp.ac], '=');
		if (!ft_check_unset(exp.tmp))
		{
			ft_print_err_2("export", av[exp.ac], "not a valid identifier", 1);
			free(exp.tmp);
			return (1);
		}
		free(exp.tmp);
		while (g_global.env[exp.j]
			&& ft_strncmp(g_global.env[exp.j], av[exp.ac], exp.i) != 0)
			exp.j++;
		ft_exec_change(exp.j, av, exp.ac, exp.i);
	}
	return (0);
}

void	ft_cmds_export(char **av)
{
	if (ft_len_arr(av) == 1)
		ft_print_var();
	else if (ft_len_arr(av) >= 2)
		if (!ft_change_var(av))
			g_global.code = 0;
}
