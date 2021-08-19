#include "Philosophers.h"

void	thread_print(int philo)
{
	printf("thread: %i", philo);
}

int main(void)
{
	pthread_t	thread_id;
	int i;
	int num_of_philo;

	i = 0;
	num_of_philo = 8;

	while (i < num_of_philo)
	{
		pthread_create(thread_id, NULL, thread_print, i);
		i++;
	}
	return(0);
}	
