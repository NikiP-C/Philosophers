/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/28 17:11:41 by nphilipp      #+#    #+#                 */
/*   Updated: 2021/09/28 20:24:34 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_philo(t_philo *philo, int message)
{
	pthread_mutex_lock(&philo->info->print);
	//printf("lock\n");
	if (philo->info->dead == 1)
		return ;
	if (message == SLEEP)
		printf("%d %d is sleeping\n", \
		get_time(philo->info->start_time), philo->num);
	else if (message == EAT)
		printf("%d %d is eating\n", \
		get_time(philo->info->start_time), philo->num);
	else if (message == THINK)
		printf("%d %d is thinking\n", \
		get_time(philo->info->start_time), philo->num);
	else if (message == FORK)
		printf("%d %d has taken a fork\n", \
		get_time(philo->info->start_time), philo->num);
	else if (message == DIED)
	{
		philo->info->dead = 1;
		printf("%d %d died\n", get_time(philo->info->start_time), philo->num);
	}
	//printf("unlock\n");
	pthread_mutex_unlock(&philo->info->print);
}
