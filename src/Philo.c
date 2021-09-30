/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/14 18:46:49 by nphilipp      #+#    #+#                 */
/*   Updated: 2021/09/29 20:42:25 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*eat_sleep_think(void *v_philo)
{
	t_philo *philo;

	philo = (t_philo *)v_philo;
	get_fork(philo);
	philo->times_eaten++;
	print_philo(philo, EAT);
	usleep(philo->info->time_to_eat);
	pthread_mutex_unlock(&philo->info->forks[philo->num - 1]);
	if (philo->num == philo->info->number_philo)
		pthread_mutex_unlock(&philo->info->forks[0]);
	else
		pthread_mutex_unlock(&philo->info->forks[philo->num]);
	print_philo(philo, SLEEP);
	usleep(philo->info->time_to_sleep);
	print_philo(philo, THINK);
	if (philo->times_eaten == philo->info->often_to_eat)
		return (0);
	eat_sleep_think(philo);
	return (0);
}

void	*thread_info(t_info *info, int philo_num)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	philo->info = info;
	philo->num = philo_num + 1;
	philo->times_eaten = 0;
	return (philo);
}

void	*keep_alive(void *v_info)
{
	t_info	*info;
	int		count;

	info = (t_info *)v_info;
	count = 0;
	while (count < info->number_philo)
	{
		if ((get_time(info->start_time) - info->last_eaten[count] \
		>= info->time_to_die))
		{
			pthread_mutex_lock(&info->print);
			printf("%lld %d died\n", get_time(info->start_time), count + 1);
			info->dead = 1;
			count = info->number_philo + 1;
			pthread_mutex_unlock(&info->print);
		}
		count++;
		if (count == info->number_philo)
			count = 0;
	}
	exit(0);
}

int	make_threads(t_info *info)
{
	int			count;
	pthread_t	*threads;
	pthread_t	checker;

	count = 0;
	threads = malloc(sizeof(pthread_t *) * info->number_philo);
	pthread_create(&checker, NULL, keep_alive, info);
	while (count < info->number_philo)
	{
		pthread_create(&threads[count], NULL, &eat_sleep_think, \
			thread_info(info, count));
		count++;
	}
	count = 0;
	while (count < info->number_philo)
	{
		pthread_join(threads[count], NULL);
		count++;
	}
	free(threads);
	free(info->forks);
	return (0);
}

int	main(int ac, char **av)
{
	if (ac != 5 && ac != 6)
	{
		printf("%d arguments given the program needs 4 or 5\n", (ac - 1));
		return (1);
	}
	make_threads(setup(ac, av));
}
