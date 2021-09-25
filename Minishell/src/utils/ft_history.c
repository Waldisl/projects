
#include "../../includes/minishell.h"

char	*ft_create_file_history(void)
{
	char	*home;

	home = ft_find_env("HOME");
	ft_add_str(&home, "/.minishell_history");
	return (home);
}

void	ft_load_file_history(void)
{
	int				fd;
	char			*line;
	char			*file_history;

	file_history = ft_create_file_history();
	fd = open(file_history, O_CREAT | O_RDWR | O_APPEND, 0777);
	while (get_next_line(fd, &line) > 0)
	{
		add_history(line);
		free(line);
	}
	free(file_history);
	close(fd);
}

void	ft_write_history(char *in)
{
	int				fd;
	char			*file_history;

	file_history = ft_create_file_history();
	fd = open(file_history, O_CREAT | O_RDWR | O_APPEND, 0777);
	ft_putstr_fd(in, fd);
	ft_putstr_fd("\n", fd);
	add_history(in);
	free(file_history);
	close(fd);
}
