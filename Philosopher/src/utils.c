
#include "phil.h"

int	ft_print(t_philosophers *pils, char *str, int i)
{
	if (pils->data_ph->f_end == 1)
		return (1);
	if (pthread_mutex_lock(pils->data_ph->print) != 0)
		return (0);
	if (i == 2)
		pils->data_ph->f_end = 1;
	printf("%ld %d %s\n", ft_time() - pils->data_ph->t_start,
		pils->pil_id, str);
	if (i == 1)
		pils->pil_ate++;
	if (pthread_mutex_unlock(pils->data_ph->print) != 0)
		return (0);
	return (1);
}

int	ft_join_destroy(pthread_t alive, t_philosophers **pils)
{
	int	i;

	if (pthread_join(alive, NULL) != 0)
		return (0);
	usleep(50);
	i = -1;
	while (++i < pils[0]->data_ph->n_pils)
	{
		if (pthread_join(pils[i]->eat, NULL) != 0)
			return (0);
		usleep(50);
		pthread_mutex_destroy(pils[i]->left);
		pthread_mutex_destroy(pils[i]->right);
	}
	return (1);
}

long	ft_time(void)
{
	struct timeval	time;
	long			k;

	gettimeofday(&time, NULL);
	k = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (k);
}

int	ft_phil1(t_data *data_ph)
{
	pthread_mutex_lock(data_ph->print);
	printf("%ld 1 has taken a left fork\n", ft_time()
		- data_ph->t_start);
	usleep(data_ph->t_died * 1000);
	printf("%ld 1 died\n", ft_time() - data_ph->t_start);
	pthread_mutex_unlock(data_ph->print);
	free(data_ph->print);
	free(data_ph->stop);
	free(data_ph);
	return (5);
}

int	ft_sleep(t_data *data_ph, long t)
{
	long	time;

	time = ft_time() - data_ph->t_start + t;
	if (time == t - 1)
		return (0);
	while (ft_time() - data_ph->t_start < time)
		usleep(10);
	return (1);
}
