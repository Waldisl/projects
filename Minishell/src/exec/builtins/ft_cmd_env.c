/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 23:54:12 by gdilly            #+#    #+#             */
/*   Updated: 2021/08/09 23:54:16 by gdilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_cmds_env(char **argv)
{
	char	**env;

	(void)argv;
	env = g_global.env;
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
	g_global.code = 0;
}
