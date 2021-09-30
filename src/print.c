/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/28 17:11:41 by nphilipp      #+#    #+#                 */
/*   Updated: 2021/09/29 20:43:59 by nphilipp      ########   odam.nl         */
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
		printf("%lld %d is sleeping\n", \
		get_time(philo->info->start_time), philo->num);
	}
	else if (message == EAT)
	{
		philo->info->last_eaten[philo->num - 1] = get_time(philo->info->start_time)
		printf("%lld %d is eating\n", \
	, philo->num);
	}
	else if (message == THINK)
		printf("%lld %d is thinking\n", \
		get_time(philo->info->start_time), philo->num);
	else if (message == FORK)
		printf("%lld %d has taken a fork\n", \
		get_time(philo->info->start_time), philo->num);
	pthread_mutex_unlock(&philo->info->print);
}
