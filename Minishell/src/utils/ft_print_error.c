/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 23:42:42 by gdilly            #+#    #+#             */
/*   Updated: 2021/08/09 23:42:45 by gdilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_print_error_1(char *err_1, char *err_str, int err_code)
{
	g_global.code = err_code;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(err_1, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(err_str, 2);
	ft_putchar_fd('\n', 2);
}

void	ft_print_err_2(char *err_1, char *err_2, char *err_str, int err_code)
{
	g_global.code = err_code;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(err_1, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(err_2, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(err_str, 2);
	ft_putchar_fd('\n', 2);
}

void	ft_print_err_code(int code, char *cmd)
{
	g_global.code = code;
	if (code == 126)
		ft_print_error_1(cmd, "command not found", 127);
}
