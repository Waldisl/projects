
#include "../../includes/minishell.h"

static bool	ft_exec_multi_cmd(t_cmds **cmd, int *i)
{
	int	save_i;
	int	fin;
	int	fout;
	int	j;

	save_i = *i;
	fin = -1;
	fout = -1;
	j = 0;
	while (j++ <= 1)
		if (!ft_check_is_multi_cmd(cmd, &save_i, &fin, &fout))
			return (false);
	ft_exec_pipe(cmd, i, fin, fout);
	return (true);
}

static bool	ft_exec_simple_cmd(t_cmds **cmd, int *i)
{
	if (cmd[*i + 1] && cmd[*i + 1]->spec == '|')
	{
		ft_exec_pipe(cmd, i, -1, -1);
		return (false);
	}
	else if (cmd[*i + 1]
		&& (cmd[*i + 1]->spec == '>' * '>' || cmd[*i + 1]->spec == '>'))
	{
		if (!ft_exec_redir_right(cmd, i))
			return (false);
	}
	else if (cmd[*i + 1]
		&& (cmd[*i + 1]->spec == '<' * '<' || cmd[*i + 1]->spec == '<'))
		ft_exec_redir_left(cmd, i);
	return (true);
}

static bool	ft_check_pipe_or_redir(t_cmds **cmd, int *i)
{
	if (ft_check_is_simple(cmd, i))
	{
		if (!ft_exec_simple_cmd(cmd, i))
			return (false);
	}
	else if (!ft_check_is_simple(cmd, i))
	{
		if (!ft_exec_multi_cmd(cmd, i))
			return (false);
	}
	return (true);
}

void	ft_exec_cmd(t_cmds	**cmd)
{
	char	**argv;
	int		i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i + 1] && cmd[i + 1]->spec)
		{
			if (!ft_check_pipe_or_redir(cmd, &i))
				continue ;
			if (!cmd[i])
				break ;
		}
		else if (cmd[i]->str)
		{
			argv = cmd[i]->argv;
			if (ft_len_arr(argv) > 0)
				ft_overwrite_env("_", argv[ft_len_arr(argv) - 1]);
			ft_exec_built(argv);
		}
		i++;
	}
}
