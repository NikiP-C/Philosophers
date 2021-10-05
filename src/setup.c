/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/14 18:55:56 by nphilipp      #+#    #+#                 */
/*   Updated: 2021/10/01 15:18:22 by nphilipp      ########   odam.nl         */
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

t_info	*setup(int ac, char **av)
{
	int				count;
	t_info			*info;

	info = malloc(sizeof(t_info));
	info->dead = 0;
	info->number_philo = ft_atoi(av[1]);
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		info->often_to_eat = ft_atoi(av[5]);
	else
		info->often_to_eat = -1;
	info->forks = malloc(sizeof(pthread_mutex_t) * info->number_philo);
	info->last_eaten = malloc(sizeof(long long) * info->number_philo);
	memset(info->last_eaten, 0, sizeof(long long) * info->number_philo);
	info->times_eaten = malloc(sizeof(int) * info->number_philo);
	memset(info->times_eaten, 0, sizeof(int) * info->number_philo);
	count = 0;
	while (count < info->number_philo)
	{
		pthread_mutex_init(&info->forks[count], NULL);
		count++;
	}
	pthread_mutex_init(&info->print, NULL);
	gettimeofday(&info->start_time, NULL);
	return (info);
}

long long	get_time(struct timeval	start_time)
{
	struct timeval	time;
	long long		time_past;

	gettimeofday(&time, NULL);
	time_past = ((time.tv_sec - start_time.tv_sec) * 1000) \
			+ ((time.tv_usec - start_time.tv_usec) / 1000);
	return (time_past);
}

void	get_fork(t_philo *philo)
{
	if (philo->num % 2)
	{
		pthread_mutex_lock(&philo->info->forks[philo->num]);
		print_philo(philo, FORK);
		if (philo->num + 1 == philo->info->number_philo)
			pthread_mutex_lock(&philo->info->forks[0]);
		else
			pthread_mutex_lock(&philo->info->forks[philo->num + 1]);
		print_philo(philo, FORK);
	}
	else
	{
		if (philo->num + 1 == philo->info->number_philo)
			pthread_mutex_lock(&philo->info->forks[0]);
		else
			pthread_mutex_lock(&philo->info->forks[philo->num + 1]);
		print_philo(philo, FORK);
		pthread_mutex_lock(&philo->info->forks[philo->num]);
		print_philo(philo, FORK);
	}
}
