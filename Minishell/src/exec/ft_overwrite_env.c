/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_overwrite_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 23:52:18 by gdilly            #+#    #+#             */
/*   Updated: 2021/08/09 23:52:18 by gdilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	ft_check_valid_env(char *env)
{
	int	i;

	i = -1;
	while (g_global.env[++i] != 0)
	{
		if (ft_strcompare(g_global.env[i], env))
			return (true);
	}
	return (false);
}

void	ft_overwrite_env(char *env, char *data)
{
	int		i;
	char	*tmp;

	i = 0;
	if (ft_check_valid_env(env))
	{
		tmp = ft_strdup(env);
		ft_add_str(&tmp, "=");
		ft_add_str(&tmp, data);
		while (g_global.env[i]
			&& ft_strncmp(g_global.env[i], env, ft_strlen(env)) != 0)
			i++;
		free(g_global.env[i]);
		g_global.env[i] = ft_strdup(tmp);
		free(tmp);
	}
}
