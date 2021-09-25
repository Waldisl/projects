/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 23:54:54 by gdilly            #+#    #+#             */
/*   Updated: 2021/08/09 23:54:55 by gdilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_cmds_pwd(void)
{
	char	buffer[4096];

	if (getcwd(buffer, 4096) == 0)
		exit(EXIT_FAILURE);
	printf("%s\n", buffer);
	g_global.code = 0;
}
