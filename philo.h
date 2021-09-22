#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_info
{
	int				start_time;
	int				number_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				often_to_eat;
	int				philo;
	int				*last_eaten;
	pthread_mutex_t	*forks;
}				t_info;

//SETUP.c
void	setup(t_info *info, int ac, char **av);
int		get_time(int start_time);
void	get_fork(t_info	*info);

#endif 