#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

enum e_messages {SLEEP, EAT, THINK, FORK, DIED};

typedef struct s_info
{
	int				start_time;
	int				number_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				often_to_eat;
	int				*last_eaten;
	int				dead;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
}				t_info;

typedef struct s_philo
{
	t_info	*info;
	int		num;
	int		times_eaten;
}				t_philo;

//SETUP.c
t_info	*setup(int ac, char **av);
int		get_time(int start_time);
void	get_fork(t_philo *philo);
void	print_philo(t_philo *philo, int message);

#endif 