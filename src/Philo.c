/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/14 18:46:49 by nphilipp      #+#    #+#                 */
/*   Updated: 2021/10/04 15:36:02 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	sleep_eat(t_philo *philo)
{
	while (philo->info->last_eaten[philo->num] + \
	philo->info->time_to_eat > get_time(philo->info->start_time))
		usleep(100);
	pthread_mutex_unlock(&philo->info->forks[philo->num]);
	if (philo->num + 1 == philo->info->number_philo)
		pthread_mutex_unlock(&philo->info->forks[0]);
	else
		pthread_mutex_unlock(&philo->info->forks[philo->num + 1]);
	print_philo(philo, SLEEP);
	while (philo->info->time_to_sleep + philo->sleep_time \
	> get_time(philo->info->start_time))
		usleep(100);
}

void	*start_thread(void *v_philo)
{
	t_philo	*philo;

	philo = (t_philo *)v_philo;
	if (philo->num % 2 == 1 && philo->info->times_eaten[philo->num] == 0)
		usleep(2000);
	check_times_eat(philo);
	get_fork(philo);
	philo->info->times_eaten[philo->num]++;
	print_philo(philo, EAT);
	sleep_eat(philo);
	print_philo(philo, THINK);
	if (philo->info->times_eaten[philo->num] == philo->info->often_to_eat)
		return (0);
	start_thread(philo);
	return (0);
}

void	*thread_info(t_info *info, int philo_num)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (philo == NULL)
		return (NULL);
	philo->info = info;
	philo->num = philo_num;
	return (philo);
}

int	make_threads(t_info *info)
{
	int			count;
	pthread_t	*threads;
	pthread_t	checker;
	void		**philo_thread;

	count = 0;
	threads = malloc(sizeof(pthread_t *) * info->number_philo);
	if (threads == NULL)
		return (print_malloc_fail(0, info, NULL));
	pthread_create(&checker, NULL, keep_alive, info);
	while (count < info->number_philo)
	{
		philo_thread[count] = thread_info(info, count);
		if (philo_thread == NULL)
			return (print_malloc_fail(void));
		pthread_create(&threads[count], NULL, &start_thread, \
			philo_thread[count]);
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
