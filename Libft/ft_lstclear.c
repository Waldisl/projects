
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*k;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		k = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = k;
	}
}
