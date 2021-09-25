/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 23:57:33 by gdilly            #+#    #+#             */
/*   Updated: 2021/08/09 23:57:34 by gdilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_exec_redir_left(t_cmds **cmd, int *i)
{
	int	save_i;

	save_i = *i;
	while (cmd[*i + 1]
		&& (cmd[*i + 1]->spec == '<' * '<' || cmd[*i + 1]->spec == '<'))
		(*i)++;
	if (cmd[*i]->spec == '<')
		ft_exec_redir_left_1(cmd[save_i], cmd[*i]);
	else if (cmd[*i]->spec == '<' * '<')
		ft_exec_redir_left_2(cmd[save_i], cmd[*i]);
}

bool	ft_exec_redir_right(t_cmds **cmd, int *i)
{
	int	save_i;

	save_i = *i;
	while (cmd[*i + 1]
		&& (cmd[*i + 1]->spec == '>' * '>'
			|| cmd[*i + 1]->spec == '>'))
	{
		(*i)++;
		if (cmd[*i + 1]
			&& (cmd[*i + 1]->spec == '>' * '>'
				|| cmd[*i + 1]->spec == '>')
			&& (cmd[*i]->spec == '>' || cmd[*i]->spec == '>' * '>')
			&& ft_check_is_file(cmd[*i]->argv[0], true) == -1)
			return (false);
	}
	if (cmd[*i]->spec == '>')
		ft_exec_redir_right_1(cmd[save_i], cmd[*i]);
	else if (cmd[*i]->spec == '>' * '>')
		ft_exec_redir_right_2(cmd[save_i], cmd[*i]);
	return (true);
}
