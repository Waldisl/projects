/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msunspot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 21:00:20 by msunspot          #+#    #+#             */
/*   Updated: 2021/09/14 01:31:30 by msunspot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

static void	ft_think_sleep(t_philosophers	*tmp)
{
	if (tmp->overeat && !tmp->data_ph->f_end)
	{
		ft_print(tmp, "is sleeping", 0);
		ft_sleep(tmp->data_ph, tmp->data_ph->t_sleep);
		ft_print(tmp, "is thinking", 0);
	}
}

static void	ft_eating(t_philosophers *tmp)
{
	ft_print(tmp, "is eating", 1);
	if (tmp->data_ph->n_eating >= 0)
	{
		if (tmp->pil_ate >= tmp->data_ph->n_eating)
		{
			tmp->data_ph->i++;
			if (tmp->data_ph->i == tmp->data_ph->n_pils)
				tmp->data_ph->f_end = 1;
			tmp->overeat = 0;
		}
	}
}

static void	*ft_eat(void *pils)
{
	t_philosophers	*tmp;

	tmp = (t_philosophers *) pils;
	while (tmp->overeat && !tmp->data_ph->f_end)
	{
		pthread_mutex_lock(tmp->left);
		ft_print(tmp, "has taken a fork", 0);
		pthread_mutex_lock(tmp->right);
		ft_print(tmp, "has taken a fork", 0);
		ft_eating(tmp);
		pthread_mutex_lock(tmp->data_ph->stop);
		tmp->pil_died = ft_time() + tmp->data_ph->t_died;
		pthread_mutex_unlock(tmp->data_ph->stop);
		ft_sleep(tmp->data_ph, tmp->data_ph->t_eat);
		pthread_mutex_unlock(tmp->left);
		pthread_mutex_unlock(tmp->right);
		ft_think_sleep(tmp);
		usleep(100);
	}
	return (NULL);
}

static void	*ft_alive(void	*pils)
{
	int				i;
	int				t;
	t_philosophers	**tmp;

	tmp = pils;
	i = 0;
	t = tmp[i]->data_ph->n_pils;
	while (!tmp[0]->data_ph->f_end)
	{
		if (i == t)
			i = 0;
		pthread_mutex_lock(tmp[i]->data_ph->stop);
		if (ft_time() > tmp[i]->pil_died)
		{
			ft_print(tmp[i], "died", 2);
			pthread_mutex_unlock(tmp[i]->data_ph->stop);
			break ;
		}
		pthread_mutex_unlock(tmp[i]->data_ph->stop);
		i++;
	}
	return (NULL);
}

int	ft_threads(t_philosophers **pils)
{
	int			i;
	int			t;
	pthread_t	alive;

	t = pils[0]->data_ph->n_pils;
	i = -1;
	while (++i < t)
		pthread_mutex_init(pils[i]->left, NULL);
	i = -1;
	if (pthread_create(&alive, NULL, ft_alive, (void *)pils) != 0)
		return (0);
	while (++i < t)
	{
		if (pthread_create(&pils[i]->eat, NULL, ft_eat, (void *)pils[i]) != 0)
			return (0);
		usleep(50);
	}
	if (!ft_join_destroy(alive, pils))
		return (0);
	return (1);
}
