
#include "../../../includes/minishell.h"

static int	ft_exec(char **argv)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == 0)
	{
		execve(argv[0], argv, g_global.env);
		exit(126);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		return (WEXITSTATUS(status));
	}
	return (1);
}

static char	**ft_get_path_exec(char *program_name)
{
	char	**path;
	char	**tmp;
	int		i;

	if (ft_strncmp(program_name, "./", 2) == 0)
	{
		path = ft_calloc(2, sizeof(char *));
		path[0] = ft_get_path_pwd();
	}
	else
	{
		tmp = ft_get_paths();
		if (ft_find_char(program_name, '/'))
		{
			path = ft_calloc(ft_len_arr(tmp) + 2, sizeof(char *));
			path[0] = ft_strdup("");
			i = -1;
			while (tmp[++i])
				path[i + 1] = ft_strdup(tmp[i]);
			ft_arr_free(tmp);
		}
		else
			path = tmp;
	}
	return (path);
}

static void	ft_argv_replace(char **str, char *tmp)
{
	if (!str)
		return ;
	free(*str);
	*str = tmp;
}

static void	ft_exec_built2(char **argv)
{
	int		i;
	char	**path;
	char	*program_name;
	int		code;
	char	*data;

	code = 126;
	program_name = ft_strdup(argv[0]);
	path = ft_get_path_exec(program_name);
	i = -1;
	while (path[++i])
	{
		data = ft_strdup(path[i]);
		ft_add_str(&data, "/");
		ft_add_str(&data, argv[0]);
		ft_argv_replace(&argv[0], data);
		code = ft_exec(argv);
		if (code != 126)
			break ;
		free(argv[0]);
		argv[0] = ft_strdup(program_name);
	}
	ft_arr_free(path);
	ft_print_err_code(code, program_name);
	free(program_name);
}

void	ft_exec_built(char **argv)
{
	if (!argv || !argv[0])
		return ;
	else if (ft_strcompare(argv[0], "env"))
		ft_cmds_env(argv);
	else if (ft_strcompare(argv[0], "export"))
		ft_cmds_export(argv);
	else if (ft_strcompare(argv[0], "unset"))
		ft_cmds_uncet(argv);
	else if (ft_strcompare(argv[0], "exit"))
		ft_cmds_exit(argv);
	else if (ft_strcompare(argv[0], "pwd"))
		ft_cmds_pwd();
	else if (ft_strcompare(argv[0], "echo"))
		ft_cmds_echo(argv);
	else if (ft_strcompare(argv[0], "cd"))
		ft_cmds_cd(argv);
	else
		ft_exec_built2(argv);
}
