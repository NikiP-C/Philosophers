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
	struct timeval	start_time;
	int				number_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				often_to_eat;
	long long		*last_eaten;
	int				*times_eaten;
	int				dead;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
}				t_info;

typedef struct s_philo
{
	t_info		*info;
	int			num;
	long long	sleep_time;
}				t_philo;

//SETUP.c
t_info			*setup(int ac, char **av);
long long		get_time(struct timeval start_time);
void			get_fork(t_philo *philo);
void			print_philo(t_philo *philo, int message);
void			check_times_eat(t_philo	*philo);
void			*keep_alive(void *v_info);
int				print_malloc_fail(int free, t_info *info, \
				pthread_t *threads, int count);

#endif 