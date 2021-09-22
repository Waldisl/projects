/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msunspot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 21:05:17 by msunspot          #+#    #+#             */
/*   Updated: 2020/11/13 21:08:40 by msunspot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
