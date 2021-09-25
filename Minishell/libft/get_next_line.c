
#include "libft.h"

void	safe_free(char **p)
{
	if (p && *p)
	{
		free(*p);
		*p = 0;
	}
}

char	*pop_line(char	**pcache)
{
	char	*new_line;
	char	*temp;
	int		d;

	temp = *pcache;
	d = ft_strchr(*pcache, '\n') - *pcache;
	new_line = ft_substr(*pcache, 0, d);
	*pcache = ft_strdup(*pcache + d + 1);
	safe_free(&temp);
	return (new_line);
}

int	append_read(int fd, char **cache)
{
	char		buf[128];
	int			r;
	char		*temp;

	r = read(fd, buf, 127);
	if (r > 0)
	{
		buf[r] = 0;
		temp = *cache;
		*cache = ft_strjoin(*cache, buf);
		safe_free(&temp);
		r = 1;
	}
	return (r);
}

int	get_next_line(int fd, char **line)
{
	static char	*cache = 0;
	int			r;

	if (!line)
		return (-1);
	r = 1;
	while (r == 1 && ft_strchr(cache, '\n') == 0)
		r = append_read(fd, &cache);
	if (r > 0)
		*line = pop_line(&cache);
	if (r <= 0 || !ft_strlen(cache))
		safe_free(&cache);
	return (r);
}
