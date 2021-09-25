/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 23:46:27 by gdilly            #+#    #+#             */
/*   Updated: 2021/08/10 00:00:04 by gdilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	ft_skip_space(char *str)
{
	while (ft_isspace(*str))
		str++;
	return (*str);
}

static void	ft_argdup(char **arg, char **tmp)
{
	*arg = ft_strdup(*tmp);
	ft_void_free((void **)tmp);
}

static int	ft_add_args_start(t_pars *pars, char cmd_str, \
								char **tmp, char **cmd_arg)
{
	if (!pars->check_mark && !pars->space
		&& !pars->mark_2 && !pars->mark_1 && ft_isspace(cmd_str))
	{
		if (ft_skip_space(*tmp))
		{
			ft_argdup(cmd_arg, tmp);
			pars->space = true;
			return (1);
		}
		else
			free(tmp);
	}
	return (0);
}

static void	ft_add_args_end(char cmd_str, char **cmd_arg, char **tmp)
{
	if (cmd_str == 0 && ft_strcompare(*cmd_arg, *tmp) == false)
	{
		if (ft_skip_space(*tmp))
			ft_argdup(cmd_arg, tmp);
		else
			free(*tmp);
	}
}

void	ft_add_args(char **cmd_arg, char *cmd_str)
{
	t_pars	pars;
	int		i;
	char	*tmp;

	tmp = 0;
	i = 0;
	pars = (t_pars){0};
	pars.space = true;
	while (*cmd_str)
	{
		ft_update_t_pars_2(*cmd_str, &pars);
		if (ft_add_args_start(&pars, *cmd_str, &tmp, &cmd_arg[i]))
			i++;
		if (pars.space && !ft_isspace(*cmd_str))
			pars.space = false;
		ft_add_char(&tmp, *cmd_str);
		cmd_str++;
		ft_add_args_end(*cmd_str, &cmd_arg[i], &tmp);
	}
}
