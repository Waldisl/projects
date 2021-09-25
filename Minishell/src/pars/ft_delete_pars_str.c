
#include "../../includes/minishell.h"

static bool	ft_check_mark(char c_1, char c_2, t_pars *pars)
{
	if (!pars->check_mark && c_1 == '"' && !pars->mark_1)
		return (true);
	if (!pars->check_mark && c_1 == '\'' && !pars->mark_2)
		return (true);
	if (!pars->check_mark && c_1 == '\\' && !pars->mark_1
		&& (c_2 == '\\' || c_2 == '"'))
		return (true);
	if (!pars->check_mark && c_1 == '\\' && !pars->mark_2
		&& !pars->mark_1 && c_2 == '\'')
		return (true);
	return (false);
}

void	ft_delete_mark(char **cmd_arg)
{
	t_pars		pars;
	int			i;
	int			j;
	char		*tmp;

	pars = (t_pars){0};
	tmp = ft_calloc(sizeof(char), ft_strlen(*cmd_arg) + 1);
	i = -1;
	j = 0;
	while ((*cmd_arg)[++i] != 0)
	{
		ft_update_t_pars_2((*cmd_arg)[i], &pars);
		if (ft_check_mark((*cmd_arg)[i], (*cmd_arg)[i + 1], &pars))
			continue ;
		tmp[j++] = (*cmd_arg)[i];
	}
	free(*cmd_arg);
	*cmd_arg = tmp;
}

void	ft_delete_backslash(char **cmd_arg)
{
	int			i;
	int			j;
	char		*tmp;
	t_pars		pars;

	pars = (t_pars){0};
	tmp = ft_calloc(sizeof(char), ft_strlen(*cmd_arg) + 1);
	i = -1;
	j = 0;
	while ((*cmd_arg)[++i] != 0)
	{
		ft_update_t_pars_2((*cmd_arg)[i], &pars);
		if (!pars.check_mark && !pars.mark_2 && !pars.mark_1
			&& (*cmd_arg)[i] == '\\' && (*cmd_arg)[i + 1] != '\\'\
			&& (*cmd_arg)[i + 1] != '\'' && (*cmd_arg)[i + 1] != '\"')
			continue ;
		if (!pars.check_mark && pars.mark_2 && (*cmd_arg)[i] == '\\'
			&& (*cmd_arg)[i + 1] == '$')
			continue ;
		tmp[j++] = (*cmd_arg)[i];
	}
	free(*cmd_arg);
	*cmd_arg = ft_strdup(tmp);
	free(tmp);
}
