/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/14 18:46:49 by nphilipp      #+#    #+#                 */
/*   Updated: 2021/09/20 15:10:14 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*eat_sleep_think(void *vinfo)
{
	t_info	*info;

	info = (t_info *)vinfo;
	get_fork(info);
	printf("%d %d starts eating\n", get_time(info->start_time), info->philo);
	info->last_eaten[info->philo] = get_time(info->last_eaten[info->philo]);
	usleep(info->time_to_eat);
	pthread_mutex_unlock(&info->forks[info->philo]);
	if (info->philo == info->number_philo - 1)
		pthread_mutex_unlock(&info->forks[0]);
	else
		pthread_mutex_unlock(&info->forks[info->philo + 1]);
	printf("%d %d starts sleeping\n", get_time(info->start_time), info->philo);
	usleep(info->time_to_sleep);
	printf("%d %d starts thinking\n", get_time(info->start_time), info->philo);
	eat_sleep_think(info);
	return (0);
}

void	*thread_info(t_info info, int philo_num)
{
	t_info	*new;

	new = malloc(sizeof(t_info));
	*new = info;
	new->philo = philo_num;
	return (new);
}

void	*keep_alive(void *vinfo)
{
	t_info	*info;
	int		count;

	info = (t_info *)vinfo;
	count = 0;
	while (count < info->number_philo)
	{
		if ((get_time(info->start_time) - info->last_eaten[count] \
		>= info->time_to_die))
		{
			printf("%d %d died\n", \
			get_time(info->start_time), count);
			count = 11;
		}
		count++;
		if (count == info->number_philo)
			count = 0;
	}
	exit(0);
}

int	make_threads(t_info info)
{
	int			count;
	pthread_t	*threads;
	pthread_t	checker;

	count = 0;
	threads = malloc(sizeof(pthread_t *) * info.number_philo);
	pthread_create(&checker, NULL, keep_alive, &info);
	printf("number of philo: %d\n", info.number_philo);
	while (count < info.number_philo)
	{
		printf("count = %d\n", count);
		info.philo = count + 1;
		pthread_create(&threads[count], NULL, &eat_sleep_think, \
			thread_info(info, count));
		count++;
	}
	count = 0;
	while (count < info.number_philo)
	{
		pthread_join(threads[count], NULL);
		count++;
	}
	free(threads);
	free(info.forks);
	return (0);
}

int	main(int ac, char **av)
{
	t_info	info;

	if (ac != 5 && ac != 6)
	{
		printf("%d arguments given the program needs 4 or 5\n", (ac - 1));
		return (1);
	}
	setup(&info, ac, av);
	printf("number of philo: %d\n", info.number_philo);
	make_threads(info);
}
