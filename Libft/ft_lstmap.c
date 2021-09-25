
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*k;
	t_list	*s;

	if (!lst || !f)
		return (NULL);
	k = ft_lstnew(f(lst->content));
	lst = lst->next;
	while (lst)
	{
		s = ft_lstnew(f(lst->content));
		if (!s)
		{
			ft_lstclear(&k, del);
			return (NULL);
		}
		ft_lstadd_back(&k, s);
		lst = lst->next;
	}
	return (k);
}
