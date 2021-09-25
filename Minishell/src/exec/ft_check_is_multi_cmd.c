
#include "../../includes/minishell.h"

static bool	ft_check_right_char(t_cmds **cmd, int *i)
{
	while (cmd[*i + 1]
		&& (cmd[*i + 1]->spec == '>' * '>' || cmd[*i + 1]->spec == '>'))
	{
		if (cmd[*i]->spec == '>' || cmd[*i]->spec == '>' * '>')
		{
			if (ft_check_is_file(cmd[*i]->argv[0], true) == -1)
				return (false);
		}
		(*i)++;
	}
	return (true);
}

bool	ft_check_is_multi_cmd(t_cmds **cmd, int *save_i, int *fin, int *fout)
{
	while (cmd[*save_i + 1] && cmd[*save_i + 1]->spec == '|')
		(*save_i)++;
	if (!ft_check_right_char(cmd, save_i))
		return (false);
	if ((cmd[*save_i]->spec == '>' * '>' || cmd[*save_i]->spec == '>'))
		*fout = *save_i;
	while (cmd[*save_i + 1]
		&& (cmd[*save_i + 1]->spec == '<' * '<'
			|| cmd[*save_i + 1]->spec == '<'))
		(*save_i)++;
	if ((cmd[*save_i]->spec == '<' * '<' || cmd[*save_i]->spec == '<'))
		*fin = *save_i;
	if (*fout == -1)
	{
		if (!ft_check_right_char(cmd, save_i))
			return (false);
		if ((cmd[*save_i]->spec == '>' * '>' || cmd[*save_i]->spec == '>'))
			*fout = *save_i;
	}
	return (true);
}
