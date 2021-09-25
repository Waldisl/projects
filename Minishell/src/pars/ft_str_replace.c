/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_replace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 23:48:24 by gdilly            #+#    #+#             */
/*   Updated: 2021/08/09 23:48:25 by gdilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_str_replace(char **cmd_arg, unsigned int start_i,
	unsigned int end_i, char *value)
{
	char	*start;
	char	*end;

	if (start_i > end_i)
		return ;
	if (start_i >= ft_strlen(*cmd_arg) || end_i >= ft_strlen(*cmd_arg))
		return ;
	start = ft_substr(*cmd_arg, 0, start_i);
	end = ft_substr(*cmd_arg, end_i + 1, ft_strlen(*cmd_arg));
	ft_add_str(&start, value);
	ft_add_str(&start, end);
	free(*cmd_arg);
	free(end);
	*cmd_arg = start;
}
