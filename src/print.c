/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/28 17:11:41 by nphilipp      #+#    #+#                 */
/*   Updated: 2021/10/05 20:42:08 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_philo(t_philo *philo, int message)
{
	pthread_mutex_lock(&philo->info->print);
	if (philo->info->dead == 1)
		return ;
	if (message == SLEEP)
	{
		philo->sleep_time = get_time(philo->info->start_time);
		printf("%lld %d is sleeping\n", philo->sleep_time, philo->num + 1);
	}
	else if (message == EAT)
	{
		philo->info->last_eaten[philo->num] = get_time(philo->info->start_time);
		printf("%lld %d is eating\n", philo->info->last_eaten[philo->num], \
		philo->num + 1);
	}
	else if (message == THINK)
		printf("%lld %d is thinking\n", \
		get_time(philo->info->start_time), philo->num + 1);
	else if (message == FORK)
		printf("%lld %d has taken a fork\n", \
		get_time(philo->info->start_time), philo->num + 1);
	pthread_mutex_unlock(&philo->info->print);
}

void	check_times_eat(t_philo	*philo)
{
	if (philo->num + 1 == philo->info->number_philo)
	{
		while (philo->info->times_eaten[philo->num] > \
			philo->info->times_eaten[0])
			  usleep(500);
	}
	else
	{
		while (philo->info->times_eaten[philo->num] > \
		philo->info->times_eaten[philo->num + 1])
			usleep(500);
	}
	if (philo->num == 0)
	{
		while (philo->info->times_eaten[philo->num] > \
			philo->info->times_eaten[philo->info->number_philo - 1])
			usleep(500);
	}
	else
	{
		while (philo->info->times_eaten[philo->num] > \
			philo->info->times_eaten[philo->num - 1])
			usleep(500);
	}
}

int	print_malloc_fail(int free, t_info *info, pthread_t *threads, int count)
{
	//int	count;

	//count = 0;
	if (free >= 2)
		free(info->forks);
	if (free >= 3)
		free(info->last_eaten);
	if (free >= 4)
		free(info->times_eaten);
	if (free >= 1)
		free(info);	
}
