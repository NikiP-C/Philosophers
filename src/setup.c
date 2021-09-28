/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/14 18:55:56 by nphilipp      #+#    #+#                 */
/*   Updated: 2021/09/28 20:25:07 by nphilipp      ########   odam.nl         */
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
	struct timeval	time1;
	int				count;
	t_info			*info;

	info = malloc(sizeof(t_info));
	printf("start of setup\n");
	count = 0;
	info->dead = 0;
	info->number_philo = ft_atoi(av[1]);
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		info->often_to_eat = ft_atoi(av[5]);
	else
		info->often_to_eat = -1;
	printf("after av\n");
	info->forks = malloc(sizeof(pthread_mutex_t) * info->number_philo);
	info->last_eaten = malloc(sizeof(int) * info->number_philo);
	memset(info->last_eaten, 0, sizeof(int) * info->number_philo);
	while (count < info->number_philo)
	{
		pthread_mutex_init(&info->forks[count], NULL);
		count++;
	}
	pthread_mutex_init(&info->print, NULL);
	gettimeofday(&time1, NULL);
	info->start_time = time1.tv_usec;
	printf("end of setup\n");
	return(info);
}

int	get_time(int start_time)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_usec - start_time);
}

void	get_fork(t_philo *philo)
{
	if (philo->num % 2)
	{
		pthread_mutex_lock(&philo->info->forks[philo->num]);
		print_philo(philo, FORK);
		if (philo->num == philo->info->number_philo - 1)
			pthread_mutex_lock(&philo->info->forks[0]);
		else
			pthread_mutex_lock(&philo->info->forks[philo->num + 1]);
		print_philo(philo, FORK);
	}
	else
	{
		if (philo->num == philo->info->number_philo - 1)
			pthread_mutex_lock(&philo->info->forks[0]);
		else
			pthread_mutex_lock(&philo->info->forks[philo->num + 1]);
		print_philo(philo, FORK);
		pthread_mutex_lock(&philo->info->forks[philo->num]);
		print_philo(philo, FORK);
	}
}
