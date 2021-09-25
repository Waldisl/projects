/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_redir_left.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 23:57:03 by gdilly            #+#    #+#             */
/*   Updated: 2021/08/09 23:57:04 by gdilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	ft_read_file_1(t_cmds *cmd_file)
{
	int		fd;
	char	*line;

	fd = ft_open_file(cmd_file->argv[0]);
	while (get_next_line(fd, &line) > 0)
	{
		write(cmd_file->fd_out, line, ft_strlen(line));
		write(cmd_file->fd_out, "\n", 1);
		free(line);
	}
	close(fd);
}

void	ft_exec_redir_left_1(t_cmds *cmd1, t_cmds *cmd_file)
{
	int		fd1[2];
	int		fork_id;

	pipe(fd1);
	fork_id = fork();
	if (fork_id == 0)
	{
		close(fd1[1]);
		cmd1->fd_in = fd1[0];
		ft_exec_all_redir(cmd1);
	}
	else
	{
		cmd_file->fd_out = fd1[1];
		ft_read_file_1(cmd_file);
	}
	close(fd1[0]);
	close(fd1[1]);
	waitpid(fork_id, NULL, 0);
}

static void	ft_read_file_2(t_cmds *end_keyword)
{
	char	*line;

	while (get_next_line(0, &line) > 0)
	{
		if (ft_strcompare(line, end_keyword->argv[0]))
		{
			free(line);
			break ;
		}
		write(end_keyword->fd_out, line, ft_strlen(line));
		write(end_keyword->fd_out, "\n", 1);
		free(line);
	}
	close(end_keyword->fd_out);
	exit(0);
}

void	ft_exec_redir_left_2(t_cmds *cmd1, t_cmds *end_keyword)
{
	int	fd1[2];
	int	fork_id;
	int	fork_id2;

	pipe(fd1);
	fork_id2 = fork();
	if (fork_id2 == 0)
	{
		close(fd1[0]);
		end_keyword->fd_out = fd1[1];
		ft_read_file_2(end_keyword);
	}
	waitpid(fork_id2, NULL, 0);
	fork_id = fork();
	if (fork_id == 0)
	{
		close(fd1[1]);
		cmd1->fd_in = fd1[0];
		ft_exec_all_redir(cmd1);
	}
	close(fd1[0]);
	close(fd1[1]);
	waitpid(fork_id, NULL, 0);
}
