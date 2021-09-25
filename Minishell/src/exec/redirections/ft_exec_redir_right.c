/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_redir_right.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 23:57:19 by gdilly            #+#    #+#             */
/*   Updated: 2021/08/09 23:57:20 by gdilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	ft_write_file_1(t_cmds *cmd_file, int fdin)
{
	int		fd;
	char	*line;

	dup2(fdin, 0);
	close(fdin);
	fd = ft_create_new_file(cmd_file->argv[0], false);
	while (get_next_line(0, &line) > 0)
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	close(0);
	exit(0);
}

void	ft_exec_redir_right_1(t_cmds *cmd1, t_cmds *cmd_file)
{
	int	fd1[2];
	int	fork_id;
	int	fork_id2;

	pipe(fd1);
	fork_id = fork();
	if (fork_id == 0)
	{
		close(fd1[0]);
		cmd1->fd_out = fd1[1];
		ft_exec_all_redir(cmd1);
	}
	fork_id2 = fork();
	if (fork_id2 == 0)
	{
		close(fd1[1]);
		ft_write_file_1(cmd_file, fd1[0]);
	}
	close(fd1[0]);
	close(fd1[1]);
	waitpid(fork_id, NULL, 0);
	waitpid(fork_id2, NULL, 0);
}

static void	ft_write_file_2(t_cmds *cmd_file, int fdin)
{
	int		fd;
	char	*line;

	dup2(fdin, 0);
	close(fdin);
	fd = ft_check_is_file(cmd_file->argv[0], false);
	while (get_next_line(0, &line) > 0)
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	close(0);
	exit(0);
}

void	ft_exec_redir_right_2(t_cmds *cmd1, t_cmds *cmd_file)
{
	int	fd1[2];
	int	fork_id;
	int	fork_id2;

	pipe(fd1);
	fork_id = fork();
	if (fork_id == 0)
	{
		close(fd1[0]);
		cmd1->fd_out = fd1[1];
		ft_exec_all_redir(cmd1);
	}
	fork_id2 = fork();
	if (fork_id2 == 0)
	{
		close(fd1[1]);
		ft_write_file_2(cmd_file, fd1[0]);
	}
	close(fd1[0]);
	close(fd1[1]);
	waitpid(fork_id, NULL, 0);
	waitpid(fork_id2, NULL, 0);
}
