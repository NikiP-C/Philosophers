/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keep_alive.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/01 15:54:15 by nphilipp      #+#    #+#                 */
/*   Updated: 2021/10/01 18:11:31 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int		check_eaten(t_info	*info)
{
	int count;

	count = 0;
	while(info->times_eaten[count] >= info->often_to_eat)
	{
		count++;
		if (count == info->number_philo)
			return(1);
	}
	return(0);
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
		{
			count = 0;
			// if (info->often_to_eat != -1 && check_eaten(info))
			// 	count = info->number_philo + 1;
			// else
			// 	count = 0;
		}
	}
	exit(0);
}
