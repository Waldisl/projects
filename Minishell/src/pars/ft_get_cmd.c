
#include "../../includes/minishell.h"

static void	ft_dop_calloc(t_cmds ***cmd)
{
	int		i;
	t_cmds	**tmp;
	t_cmds	**cmd_dop;

	cmd_dop = *cmd;
	i = -1;
	while (cmd_dop[++i])
		;
	tmp = ft_calloc(i + 2, sizeof(t_cmds *));
	i = -1;
	while (cmd_dop[++i])
		tmp[i] = cmd_dop[i];
	tmp[i] = ft_calloc(1, sizeof(t_cmds));
	free(cmd_dop);
	*cmd = tmp;
}

static bool	ft_check_create_cmd(char **cmd_str, t_pars *pars,
	t_cmds ***cmd, int *i)
{
	int		spec;
	char	*str;

	str = *cmd_str;
	if (!pars->check_mark && !pars->mark_1 && !pars->mark_2
		&& ft_ischar(*str, "<>|;&"))
	{
		ft_dop_calloc(cmd);
		(*i)++;
		spec = *str;
		if (ft_check_char(*str, *(str + 1), "<>|&"))
		{
			spec *= spec;
			(*cmd_str)++;
		}
		(*cmd)[*i]->spec = spec;
		return (true);
	}
	return (false);
}

static void	ft_get_cmds_arg(t_cmds **cmd)
{
	int	i;

	if (!cmd)
		return ;
	i = -1;
	while (cmd[++i])
	{
		if (cmd[i]->str)
			cmd[i]->argv = ft_pars(cmd[i]->str);
	}
}

t_cmds	**ft_get_cmds(char *cmd_str)
{
	t_cmds		**cmd;
	t_pars		pars;
	int			i;

	i = 0;
	cmd = ft_calloc(2, sizeof(t_cmds *));
	cmd[i] = ft_calloc(1, sizeof(t_cmds));
	pars = (t_pars){0};
	while (*cmd_str)
	{
		ft_update_t_pars_2(*cmd_str, &pars);
		if (!ft_check_create_cmd(&cmd_str, &pars, &cmd, &i))
			ft_add_char(&cmd[i]->str, *cmd_str);
		cmd_str++;
	}
	if (!ft_check_cmd(cmd))
	{
		ft_free_cmd(cmd);
		return (NULL);
	}
	ft_get_cmds_arg(cmd);
	return (cmd);
}
