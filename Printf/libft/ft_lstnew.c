
#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list *g;

	if (!(g = malloc(sizeof(*g))))
		return (NULL);
	g->content = content;
	g->next = NULL;
	return (g);
}
