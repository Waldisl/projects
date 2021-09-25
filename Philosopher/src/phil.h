
#ifndef PHIL_H
# define PHIL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include "struct.h"

int		ft_sleep(t_data *data_ph, long t);
int		ft_phil1(t_data *data_ph);
int		ft_threads(t_philosophers **pils);
int		ft_print(t_philosophers *pils, char *str, int i);
int		ft_atoi(char *str);
int		ft_valid_args(char **argv);
void	ft_free_struct(t_philosophers **pils, t_data *data_ph);
int		ft_join_destroy(pthread_t alive, t_philosophers **pils);
long	ft_time(void);

#endif