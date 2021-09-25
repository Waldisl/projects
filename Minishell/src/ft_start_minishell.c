
#include "../includes/minishell.h"

void	ft_start_minishell(void)
{
	char			*cmd_str;
	char			*cmd_name;
	t_cmds			**cmd;

	ft_load_file_history();
	while (1)
	{
		cmd_name = ft_strdup("minishell> ");
		cmd_str = readline(cmd_name);
		if (!cmd_str)
			ft_cmds_exit(0);
		if (cmd_str[0])
			ft_write_history(cmd_str);
		cmd = ft_get_cmds(cmd_str);
		if (cmd)
			ft_exec_cmd(cmd);
		ft_free_cmd(cmd);
		free(cmd_str);
		free(cmd_name);
	}
}
