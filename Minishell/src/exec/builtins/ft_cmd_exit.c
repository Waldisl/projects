/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msunspot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 22:49:49 by msunspot          #+#    #+#             */
/*   Updated: 2021/08/10 22:49:52 by msunspot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_cmds_exit(char **argv)
{
	g_global.code = 0;
	if (ft_len_arr(argv) > 1)
	{
		if (!ft_str_isdigit(argv[1]))
		{
			printf("exit\n");
			ft_print_err_2("exit", argv[1], "numeric argument required", 255);
			exit(2);
			return ;
		}
		else if (ft_len_arr(argv) != 2)
		{
			ft_print_err_2("exit", argv[1], "too many arguments", 1);
			return ;
		}
		else
			g_global.code = ft_atoi(argv[1]);
	}
	printf("exit\n");
	exit(g_global.code);
}
