
#include "../includes/minishell.h"

static void	ft_get_envp(char **envp)
{
	int	i;

	i = -1;
	g_global = (t_global){0};
	g_global.env = ft_calloc(sizeof(char *), ft_len_arr(envp) + 1);
	while (envp[++i])
		g_global.env[i] = ft_strdup(envp[i]);
}

static void	ft_sig_handle(int signal)
{
	int	n;

	if (signal == SIGINT)
	{
		printf("\b\b  \b\b");
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signal == SIGQUIT)
		printf("\b\b  \b\b");
	wait(&n);
	if (n == 2 || n == 3)
	{
		if (signal == 2)
			ft_putchar_fd('\r', 1);
		if (signal == 3)
			ft_putendl_fd("Quit: 3", 1);
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	ft_get_envp(envp);
	signal(SIGINT, ft_sig_handle);
	signal(SIGQUIT, ft_sig_handle);
	ft_start_minishell();
	return (0);
}
