/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 23:46:41 by gdilly            #+#    #+#             */
/*   Updated: 2021/08/10 01:10:35 by gdilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
static char	*ft_check_spec_char(int nb)
{
	if (nb == '>' * '>')
		return (">>");
	else if (nb == '<' * '<')
		return ("<<");
	else if (nb == '|' * '|')
		return ("||");
	else if (nb == '&' * '&')
		return ("&&");
	else if (nb == '|')
		return ("|");
	else if (nb == '<')
		return ("<");
	else if (nb == '>')
		return (">");
	else if (nb == ';')
		return (";");
	else if (nb == '&')
		return ("&");
	return (NULL);
}

static bool	ft_check_first_cmds(t_cmds **cmd)
{
	char	*str_error;

	if (cmd[1] && cmd[0]->spec == 0 && cmd[0]->str == 0
		&& cmd[1]->spec != 0)
	{
		str_error = ft_check_spec_char(cmd[1]->spec);
		ft_print_error_1("syntax error near unexpected token", str_error, 2);
		return (false);
	}
	return (true);
}

static bool	ft_check_semicolon(t_cmds **cmd, int i)
{
	char	*str_error;

	if (cmd[i + 1] && cmd[i]->spec == ';' && cmd[i + 1]->spec == ';'
		&& !cmd[i]->str)
	{
		ft_print_error_1("syntax error near unexpected token", ";;", 2);
		return (false);
	}
	else if (cmd[i]->spec == ';')
		cmd[i]->spec = 0;
	if (cmd[i + 1] && cmd[i]->spec == 0 && cmd[i + 1]->spec != 0
		&& (ft_strcompare(cmd[i]->str, " ") || !cmd[i]->str))
	{
		str_error = ft_check_spec_char(cmd[i + 1]->spec);
		ft_print_error_1("syntax error near unexpected token", str_error, 2);
		return (false);
	}
	return (true);
}

static bool	ft_check_separator(t_cmds **cmd, int i)
{
	char	*str_error;

	if (cmd[i + 1] && cmd[i]->spec != 0 && cmd[i + 1]->spec != 0
		&& (ft_strcompare(cmd[i]->str, " ") || !cmd[i]->str))
	{
		str_error = ft_check_spec_char(cmd[i + 1]->spec);
		ft_print_error_1("syntax error near unexpected token", str_error, 2);
		return (false);
	}
	return (true);
}

bool	ft_check_cmd(t_cmds	**cmd)
{
	int		i;

	i = -1;
	if (!ft_check_first_cmds(cmd))
		return (false);
	while (cmd[++i])
	{
		if (cmd[i]->spec == 0)
			continue ;
		if (!ft_check_semicolon(cmd, i)
			|| !ft_check_separator(cmd, i))
			return (false);
	}
	if (!cmd[i - 1]->str && cmd[i - 1]->spec)
		return (false);
	return (true);
}
