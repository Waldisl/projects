/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 23:56:48 by gdilly            #+#    #+#             */
/*   Updated: 2021/08/09 23:56:49 by gdilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	ft_exec_child_redir(t_cmds *cmd)
{
	int		fork_id;

	fork_id = fork();
	if (fork_id == 0)
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
	waitpid(fork_id, NULL, 0);
}

static void	ft_close_fd(t_cmds *cmd, int std_in, int std_out)
{
	if (cmd->fd_in)
		close(cmd->fd_in);
	if (cmd->fd_out)
		close(cmd->fd_out);
	dup2(std_in, 0);
	dup2(std_out, 1);
}

static bool	ft_st_1(t_cmds **cmds, int icmd, int *fd_in)
{
	if (icmd == -1)
		*fd_in = dup(0);
	else
		*fd_in = ft_open_file(cmds[icmd]->argv[0]);
	return (*fd_in != -1);
}

static bool	ft_st_2(t_cmds **cmds, int ocmd, int *fd_out)
{
	if (ocmd == -1)
		*fd_out = dup(0);
	else
	{
		if (cmds[ocmd]->spec == '>')
			*fd_out = ft_create_new_file(cmds[ocmd]->argv[0], false);
		else
			*fd_out = ft_check_is_file(cmds[ocmd]->argv[0], false);
	}
	return (*fd_out != -1);
}

void	ft_exec_pipe(t_cmds **cmds, int *i, int icmd, int ocmd)
{
	t_pipe	fdp;

	fdp.std_in = dup(0);
	fdp.std_out = dup(1);
	if (!ft_st_1(cmds, icmd, &fdp.fd_in) || !ft_st_2(cmds, ocmd, &fdp.fd_out))
		return ;
	fdp.flag = true;
	while (cmds[*i] && (fdp.flag || cmds[*i]->spec == '|'))
	{
		cmds[*i]->fd_in = fdp.fd_in;
		if (cmds[*i + 1] && cmds[*i + 1]->spec == '|')
		{
			pipe(fdp.pipes);
			cmds[*i]->fd_out = fdp.pipes[1];
			fdp.fd_in = fdp.pipes[0];
		}
		else
			cmds[*i]->fd_out = fdp.fd_out;
		ft_exec_child_redir(cmds[*i]);
		ft_close_fd(cmds[*i], fdp.std_in, fdp.std_out);
		fdp.flag = false;
		(*i)++;
	}
	if (icmd != -1 || ocmd != -1)
		*i = ft_return_more_value(icmd, ocmd);
}
