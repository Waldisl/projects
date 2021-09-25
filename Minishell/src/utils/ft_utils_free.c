/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 23:43:39 by gdilly            #+#    #+#             */
/*   Updated: 2021/08/09 23:43:40 by gdilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_cmd(t_cmds **cmd)
{
	int	i;

	if (!cmd)
		return ;
	i = -1;
	while (cmd[++i])
	{
		if (cmd[i]->str)
			free(cmd[i]->str);
		if (cmd[i]->argv)
			ft_arr_free(cmd[i]->argv);
		free(cmd[i]);
	}
	free(cmd);
}

void	ft_arr_free(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

void	ft_void_free(void **p)
{
	if (*p)
	{
		free(*p);
		*p = NULL;
	}
}
