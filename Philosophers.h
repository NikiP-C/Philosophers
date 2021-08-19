#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>

typedef struct s_philosopher
{
	int	time_eaten;
	int	time_eaten;
}				t_philosopher;

typedef struct s_info
{
	int	number_philo;
	int	time_to_eat;
	int	time_to_sleep;
	int	often_to_eat;
}				t_info;

#endif 