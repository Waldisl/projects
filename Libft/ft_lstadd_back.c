
#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*k;

	if (!new || !lst)
		return ;
	if (*lst)
	{
		k = *lst;
		while (k->next)
			k = k->next;
		k->next = new;
	}
	else
		*lst = new;
}
