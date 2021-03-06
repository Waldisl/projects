
#include "../../includes/minishell.h"

static bool	ft_check_is_pipe(t_cmds **cmd, int *i)
{
	int	j;

	j = *i;
	while (cmd[j + 1] && cmd[j + 1]->spec == '|')
		j++;
	if (cmd[j + 1] && cmd[j + 1]->spec != '|')
		return (false);
	return (true);
}

static bool	ft_check_is_left_redir(t_cmds **cmd, int *i)
{
	int	j;

	j = *i;
	while (cmd[j + 1]
		&& (cmd[j + 1]->spec == '<' * '<' || cmd[j + 1]->spec == '<'))
		j++;
	if (cmd[j + 1]
		&& (cmd[j + 1]->spec != '<' * '<' || cmd[j + 1]->spec != '<'))
		return (false);
	return (true);
}

static bool	ft_check_is_right_redir(t_cmds **cmd, int *i)
{
	int	j;

	j = *i;
	while (cmd[j + 1]
		&& (cmd[j + 1]->spec == '>' * '>' || cmd[j + 1]->spec == '>'))
		j++;
	if (cmd[j + 1]
		&& (cmd[j + 1]->spec != '>' * '>' || cmd[j + 1]->spec != '>'))
		return (false);
	return (true);
}

bool	ft_check_is_simple(t_cmds **cmd, int *i)
{
	int	j;

	j = *i;
	if (cmd[j + 1] && cmd[j + 1]->spec == '|')
	{
		if (!ft_check_is_pipe(cmd, &j))
			return (false);
	}
	else if (cmd[j + 1]
		&& (cmd[j + 1]->spec == '>' * '>' || cmd[j + 1]->spec == '>'))
	{
		if (!ft_check_is_right_redir(cmd, &j))
			return (false);
	}
	else if (cmd[j + 1]
		&& (cmd[j + 1]->spec == '<' * '<' || cmd[j + 1]->spec == '<'))
	{
		if (!ft_check_is_left_redir(cmd, &j))
			return (false);
	}
	return (true);
}
