/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/14 18:46:49 by nphilipp      #+#    #+#                 */
/*   Updated: 2021/09/28 20:26:35 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*eat_sleep_think(void *v_philo)
{
	t_philo *philo;

	printf("start of est\n");
	philo = (t_philo *)v_philo;
	get_fork(philo);
	philo->times_eaten++;
	print_philo(philo, EAT);
	philo->info->last_eaten[philo->num] = get_time(philo->info->last_eaten[philo->num]);
	usleep(philo->info->time_to_eat);
	pthread_mutex_unlock(&philo->info->forks[philo->num]);
	if (philo->num == philo->info->number_philo - 1)
		pthread_mutex_unlock(&philo->info->forks[0]);
	else
		pthread_mutex_unlock(&philo->info->forks[philo->num + 1]);
	print_philo(philo, SLEEP);
	usleep(philo->info->time_to_sleep);
	print_philo(philo, THINK);
	if (philo->times_eaten == philo->info->often_to_eat)
		return (0);
	printf("end of est\n");
	eat_sleep_think(philo);
	return (0);
}

void	*thread_info(t_info *info, int philo_num)
{
	t_philo	*philo;

	printf("start of making struct\n");
	philo = malloc(sizeof(t_philo));
	philo->info = info;
	philo->num = philo_num + 1;
	philo->times_eaten = 0;
	printf("end making sturct\n");
	return (philo);
}

void	*keep_alive(void *v_philo)
{
	t_philo	*philo;
	int		count;

	philo = (t_philo *)v_philo;
	count = 0;
	while (count < philo->info->number_philo)
	{
		if ((get_time(philo->info->start_time) - philo->info->last_eaten[count] \
		>= philo->info->time_to_die))
		{
			print_philo(philo, DIED);
			count = philo->info->number_philo + 1;
		}
		count++;
		if (count == philo->info->number_philo)
			count = 0;
	}
	exit(0);
}

int	make_threads(t_info *info)
{
	int			count;
	pthread_t	*threads;
	pthread_t	checker;

	printf("beginning of make threads\n");
	count = 0;
	threads = malloc(sizeof(pthread_t *) * info->number_philo);
	pthread_create(&checker, NULL, keep_alive, info);
	while (count < info->number_philo)
	{
		printf("making the threads\n");
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
