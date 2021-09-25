/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 23:55:13 by gdilly            #+#    #+#             */
/*   Updated: 2021/08/09 23:55:13 by gdilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_delete_var(int j, int i, char **argv)
{
	int		k;
	char	**env;

	if (g_global.env[j] && ft_strncmp(g_global.env[j], \
		argv[i], ft_strlen(argv[i])) == 0)
	{
		env = ft_calloc(sizeof(char *), ft_len_arr(g_global.env));
		k = 0;
		while (k < j)
		{
			env[k] = ft_strdup(g_global.env[k]);
			k++;
		}
		j++;
		while (g_global.env[j])
		{
			env[k] = ft_strdup(g_global.env[j]);
			j++;
			k++;
		}
		ft_arr_free(g_global.env);
		g_global.env = env;
	}
}

void	ft_cmds_uncet(char **argv)
{
	int		i;
	int		j;
	int		argc;

	i = 0;
	argc = ft_len_arr(argv);
	if (argc > 1)
	{
		while (argv[++i])
		{
			j = 0;
			if (ft_check_unset(argv[i]) == 0)
			{
				ft_print_err_2("unset", argv[i], "not a valid identifier", 1);
				return ;
			}
			while (g_global.env[j] && ft_strncmp(g_global.env[j], \
				argv[i], ft_strlen(argv[i])) != 0)
				j++;
			ft_delete_var(j, i, argv);
		}
	}
	g_global.code = 0;
}
