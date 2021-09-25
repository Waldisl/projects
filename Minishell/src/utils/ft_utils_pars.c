/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_pars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 23:43:51 by gdilly            #+#    #+#             */
/*   Updated: 2021/08/09 23:43:52 by gdilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_ischar(char c, const char *str)
{
	while (*str)
	{
		if (*str == c)
			return (true);
		str++;
	}
	return (false);
}

bool	ft_check_char(char c_1, char c_2, char *set)
{
	while (*set)
	{
		if (c_1 == *set && c_2 == *set)
			return (true);
		set++;
	}
	return (false);
}
