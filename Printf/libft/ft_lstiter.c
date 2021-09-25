
#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*k;

	if (!lst || !f)
		return ;
	k = lst;
	while (k)
	{
		f(k->content);
		k = k->next;
	}
}
