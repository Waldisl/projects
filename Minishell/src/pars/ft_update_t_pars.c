/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_t_pars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 23:48:36 by gdilly            #+#    #+#             */
/*   Updated: 2021/08/09 23:48:37 by gdilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_update_t_pars_2(char c, t_pars *parsing)
{
	parsing->mark_1 = parsing->flag_1;
	parsing->mark_2 = parsing->flag_2;
	if (parsing->check_mark)
		parsing->check_mark = false;
	else if (parsing->dop_flag)
	{
		parsing->check_mark = true;
		parsing->dop_flag = false;
	}
	if (c == '\\' && !parsing->mark_1 && !parsing->check_mark)
		parsing->dop_flag = true;
	if (c == '\'' && !parsing->mark_2 && !parsing->check_mark)
		parsing->flag_1 = !parsing->flag_1;
	if (c == '"' && !parsing->mark_1 && !parsing->check_mark)
		parsing->flag_2 = !parsing->flag_2;
}
