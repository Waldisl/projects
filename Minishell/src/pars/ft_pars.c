/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 23:47:59 by gdilly            #+#    #+#             */
/*   Updated: 2021/08/10 01:11:47 by gdilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_update_t_pars_1(char c, t_pars *pars)
{
	if (pars->check_mark)
		pars->check_mark = false;
	else
	{
		if (c == '\\' && !pars->mark_1)
			pars->check_mark = true;
		if (c == '"' && !pars->mark_1)
			pars->mark_2 = !pars->mark_2;
		if (c == '\'' && !pars->mark_2)
			pars->mark_1 = !pars->mark_1;
	}
}

static bool	ft_check_valid_cmd(char *cmd_str)
{
	t_pars	pars;

	pars = (t_pars){0};
	while (*cmd_str)
	{
		ft_update_t_pars_1(*cmd_str, &pars);
		cmd_str++;
	}
	return (!pars.mark_2 && !pars.mark_1 && !pars.check_mark);
}

int	ft_argclen(char *cmd_str)
{
	t_pars	pars;
	int		i;

	i = 0;
	pars = (t_pars){0};
	pars.space = true;
	while (*cmd_str)
	{
		ft_update_t_pars_1(*cmd_str, &pars);
		if (!pars.space && !pars.mark_2 && \
			!pars.mark_1 && ft_isspace(*cmd_str))
			pars.space = true;
		if (pars.space && !ft_isspace(*cmd_str))
		{
			pars.space = false;
			i++;
		}
		cmd_str++;
	}
	return (i);
}

static void	ft_argtrim(char **cmd_arg, const char *set)
{
	char	*tmp;

	tmp = ft_strtrim(*cmd_arg, set);
	free(*cmd_arg);
	*cmd_arg = tmp;
}

char	**ft_pars(char *cmd_str)
{
	char	**cmd_arg;
	int		len;
	int		i;

	if (!ft_check_valid_cmd(cmd_str))
		return (NULL);
	len = ft_argclen(cmd_str);
	cmd_arg = ft_calloc(sizeof(char *), len + 1);
	ft_add_args(cmd_arg, cmd_str);
	i = -1;
	while (cmd_arg[++i])
	{
		ft_argtrim(&cmd_arg[i], " \t\n\v\f\r");
		ft_check_env(&cmd_arg[i]);
		ft_check_str_code(&cmd_arg[i]);
		ft_check_tilde(&cmd_arg[i]);
		ft_delete_backslash(&cmd_arg[i]);
		ft_delete_mark(&cmd_arg[i]);
	}
	return (cmd_arg);
}
