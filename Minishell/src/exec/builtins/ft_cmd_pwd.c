
#include "../../../includes/minishell.h"

void	ft_cmds_pwd(void)
{
	char	buffer[4096];

	if (getcwd(buffer, 4096) == 0)
		exit(EXIT_FAILURE);
	printf("%s\n", buffer);
	g_global.code = 0;
}
