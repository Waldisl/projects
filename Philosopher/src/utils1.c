
#include "phil.h"

static int	ft_number(char *str)
{
	while (*str)
	{
		if (48 > *str || *str > 57)
			return (0);
		str++;
	}
	return (1);
}

int	ft_valid_args(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!ft_number(argv[i++]))
		{
			printf("%s\n", "The argument should be a number");
			return (0);
		}
	}
	if (ft_atoi(argv[1]) < 1)
	{
		printf("%s\n", "Philosophers less than one");
		return (0);
	}
	return (1);
}

static int	ft_tern(int b)
{
	if (b < 0)
		return (0);
	return (-1);
}

int	ft_atoi(char *str)
{
	int	a;
	int	b;

	b = 1;
	a = 0;
	while (*str && (*str == ' ' || *str == '\n' || *str == '\t' || \
				*str == '\v' || *str == '\f' || *str == '\r'))
		str++;
	if (*str == '-')
		b = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str && *str >= '0' && *str <= '9')
	{
		if ((a * 10) < a)
			return (ft_tern(b));
		a = a * 10 + (*str - 48);
		str++;
	}
	return (a * b);
}

void	ft_free_struct(t_philosophers **pils, t_data *data_ph)
{
	int	i;

	i = data_ph->n_pils;
	while (i-- > 0)
	{
		if (pils[i] != NULL)
		{
			free(pils[i]->left);
			free(pils[i]);
		}
	}
	pthread_mutex_destroy(data_ph->print);
	pthread_mutex_destroy(data_ph->stop);
	free(data_ph->print);
	free(data_ph->stop);
	free(pils);
	free(data_ph);
}
