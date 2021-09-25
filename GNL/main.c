
#include "get_next_line.h"

int	main(void)
{
	char	*line;
	int		fd;
	int		i;

	fd = open("test.txt", O_RDONLY);
	while ((i = get_next_line(fd, &line)) >= 0)
	{
		printf("%s\n", line);
		free(line);
		if (i == 0)
			break ;
	}
	close(fd);
	return (0);
}
