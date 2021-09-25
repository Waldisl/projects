
#include "../../../includes/minishell.h"

void	ft_cmds_env(char **argv)
{
	char	**env;

	(void)argv;
	env = g_global.env;
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
	g_global.code = 0;
}
