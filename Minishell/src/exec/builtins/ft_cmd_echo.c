/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 23:53:56 by gdilly            #+#    #+#             */
/*   Updated: 2021/08/09 23:53:57 by gdilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	ft_putargs(char **argv)
{
	while (*argv)
	{
		ft_putstr_fd(*argv, 1);
		if (*(argv + 1) != NULL)
			ft_putchar_fd(' ', 1);
		argv++;
	}
}

static bool	ft_check_flag(char *str)
{
	int	i;

	i = 0;
	if (str[i] && str[i] == '-')
	{
		i++;
		while (str[i])
		{
			if (str[i] != 'n' && str[i] != 'e' && str[i] != 'E')
				return (false);
			i++;
		}
		return (true);
	}
	return (false);
}

void	ft_cmds_echo(char **argv)
{
	bool	flag;

	argv++;
	flag = false;
	while (*argv && ft_check_flag(*argv))
	{
		flag = true;
		argv++;
	}
	ft_putargs(argv);
	if (!flag)
		ft_putchar_fd('\n', 1);
	g_global.code = 0;
}
