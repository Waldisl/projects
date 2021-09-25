/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msunspot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 21:15:30 by msunspot          #+#    #+#             */
/*   Updated: 2020/11/14 19:18:50 by msunspot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
