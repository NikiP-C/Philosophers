/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/14 18:55:56 by nphilipp      #+#    #+#                 */
/*   Updated: 2021/09/20 14:07:11 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int	ft_atoi(char *str)
{
	int	num;
	int	neg;
	int	i;

	num = 0;
	neg = 1;
	i = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg = -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = (num * 10) + str[i] - '0';
		i++;
	}
	return (num * neg);
}

void	setup(t_info *info, int ac, char **av)
{
	struct timeval	time1;
	int				count;

	count = 0;
	info->number_philo = ft_atoi(av[1]);
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		info->often_to_eat = ft_atoi(av[5]);
	gettimeofday(&time1, NULL);
	info->start_time = time1.tv_usec;
	info->forks = malloc(sizeof(pthread_mutex_t) * info->number_philo);
	info->last_eaten = malloc(sizeof(int) * info->number_philo);
	memset(info->last_eaten, 0, sizeof(int) * info->number_philo);
	while (count < info->number_philo)
	{
		pthread_mutex_init(&info->forks[count], NULL);
		count++;
	}
}

int	get_time(int start_time)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_usec - start_time);
}

void	get_fork(t_info	*info)
{
	if (info->philo % 2)
	{
		pthread_mutex_lock(&info->forks[info->philo]);
		printf("%d %d has taken a fork\n", \
		get_time(info->start_time), info->philo);
		if (info->philo == info->number_philo - 1)
			pthread_mutex_lock(&info->forks[0]);
		else
			pthread_mutex_lock(&info->forks[info->philo + 1]);
		printf("%d %d has taken a fork\n", \
		get_time(info->start_time), info->philo);
	}
	else
	{
		if (info->philo == info->number_philo - 1)
			pthread_mutex_lock(&info->forks[0]);
		else
			pthread_mutex_lock(&info->forks[info->philo + 1]);
		printf("%d %d has taken a fork\n", \
		get_time(info->start_time), info->philo);
		pthread_mutex_lock(&info->forks[info->philo]);
		printf("%d %d has taken a fork\n", \
		get_time(info->start_time), info->philo);
	}
}
