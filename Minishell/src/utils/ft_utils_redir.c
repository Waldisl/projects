/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 23:44:10 by gdilly            #+#    #+#             */
/*   Updated: 2021/08/09 23:44:11 by gdilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exec_all_redir(t_cmds *cmd)
{
	if (cmd->fd_in)
	{
		dup2(cmd->fd_in, 0);
		close(cmd->fd_in);
	}
	if (cmd->fd_out)
	{
		dup2(cmd->fd_out, 1);
		close(cmd->fd_out);
	}
	ft_exec_built(cmd->argv);
	close(1);
	close(0);
	exit(0);
}

int	ft_check_is_file(char *str, bool should_close)
{
	int	fd;

	fd = open(str, O_CREAT | O_APPEND | O_WRONLY, 0777);
	if (fd == -1)
	{
		ft_print_error_1(str, "Is a directory", 1);
		return (fd);
	}
	if (should_close)
		close(fd);
	return (fd);
}

int	ft_create_new_file(char *str, bool should_close)
{
	int	fd;

	fd = open(str, O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (fd == -1)
	{
		ft_print_error_1(str, "Is a directory", 1);
		return (fd);
	}
	if (should_close)
		close(fd);
	return (fd);
}

int	ft_open_file(char *str)
{
	int			fd;
	struct stat	buf;
	int			flag;

	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		flag = stat(str, &buf);
		if (flag == -1)
			ft_print_err_2("cd", str, "No such file or directory", 1);
		else if (flag == 0)
			ft_print_error_1("cd", "Not a directory", 1);
	}
	return (fd);
}

int	ft_return_more_value(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}
