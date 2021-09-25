
#include "phil.h"

static int	ft_pars2(char **argv, t_data *data_ph)
{
	data_ph->stop = malloc(sizeof(pthread_mutex_t));
	if (!data_ph->stop)
		return (0);
	pthread_mutex_init(data_ph->stop, NULL);
	if (argv[5])
		data_ph->n_eating = ft_atoi(argv[5]);
	else
		data_ph->n_eating = -1;
	data_ph->print = malloc(sizeof(pthread_mutex_t));
	if (!data_ph->print)
		return (0);
	return (1);
}

static int	ft_pars(char **argv, t_data *data_ph)
{
	if (!ft_valid_args(argv))
		return (0);
	data_ph->n_pils = ft_atoi(argv[1]);
	data_ph->t_died = ft_atoi(argv[2]);
	data_ph->t_eat = ft_atoi(argv[3]);
	data_ph->t_sleep = ft_atoi(argv[4]);
	data_ph->f_end = 0;
	data_ph->i = 0;
	if (ft_pars2(argv, data_ph) == 0)
		return (0);
	data_ph->t_start = ft_time();
	if (!data_ph->print || pthread_mutex_init(data_ph->print, NULL)
		|| data_ph->t_died < 1 || data_ph->t_eat < 1
		|| data_ph->t_sleep < 1 || data_ph->n_eating < -1)
	{
		free(data_ph->stop);
		free(data_ph->print);
		return (0);
	}
	if (data_ph->n_pils == 1)
		return (ft_phil1(data_ph));
	return (1);
}

static int	ft_philo_struct(t_data *data_ph, t_philosophers **pils)
{
	int	i;

	i = -1;
	while (++i < data_ph->n_pils)
	{
		pils[i] = (t_philosophers *)malloc(sizeof(t_philosophers));
		if (!pils[i])
			return (0);
		pils[i]->pil_id = i + 1;
		pils[i]->pil_ate = 0;
		pils[i]->overeat = 1;
		pils[i]->left = malloc(sizeof(pthread_mutex_t));
		if (!pils[i]->left)
			return (0);
		pils[i]->data_ph = data_ph;
		pils[i]->pil_died = ft_time() + pils[i]->data_ph->t_died;
		if (i > 0 && pils[i]->left)
			pils[i - 1]->right = pils[i]->left;
	}
	pils[i - 1]->right = pils[0]->left;
	pils[i] = NULL;
	return (1);
}

static int	ft_philosophers(char **argv)
{
	t_data			*data_ph;
	t_philosophers	**pils;
	int				pars;

	data_ph = malloc(sizeof(t_data));
	if (!data_ph)
		return (0);
	pars = ft_pars(argv, data_ph);
	if (!pars)
	{
		free(data_ph);
		return (0);
	}
	else if (pars == 5)
		return (1);
	pils = (t_philosophers **)malloc(sizeof(t_philosophers *)
			* (data_ph->n_pils + 1));
	if (!pils)
		return (0);
	if (!ft_philo_struct(data_ph, pils) || !ft_threads(pils))
		return (0);
	ft_free_struct(pils, data_ph);
	return (1);
}

int	main(int argc, char **argv)
{
	if (argc > 6 || argc < 5 )
	{
		printf("%s\n", "The number of arguments is incorrect");
		return (-1);
	}
	if (!ft_philosophers(argv))
		return (-1);
	return (0);
}
