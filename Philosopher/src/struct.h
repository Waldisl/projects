
#ifndef STRUCT_H
# define STRUCT_H

# include "phil.h"

typedef struct s_data
{
	int				n_pils;
	int				t_died;
	int				t_eat;
	int				t_sleep;
	int				n_eating;
	long			t_start;
	int				f_end;
	int				i;
	pthread_mutex_t	*print;
	pthread_mutex_t	*stop;
}				t_data;

typedef struct s_philosophers
{
	int				pil_id;
	int				pil_ate;
	int				overeat;
	long			pil_died;
	pthread_t		eat;
	pthread_mutex_t	*right;
	pthread_mutex_t	*left;
	t_data			*data_ph;
}				t_philosophers;

#endif
