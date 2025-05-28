#include "philo_header.h"

void	*monitor(void *arg)
{
	t_info_of_each_philo	*philos = (t_info_of_each_philo *)arg;
	t_philo_info			*info = philos[0].genr_info;
	long					now;
	int						i;


    // run until a philo dies or all are full
	while (1)
	{
		i = 0;
        // each philo
		while (i < info->number_of_philo)
		{
			pthread_mutex_lock(&philos[i].meal_lock);
            long last_meal = philos[i].last_meal_time;
            pthread_mutex_unlock(&philos[i].meal_lock);
            if (now - last_meal > info->time_to_die)
			{
                // print philo id and time die
				long timestamp = now - info->gen_time_start;
				printf("%ld %d died\n", timestamp, philos[i].ID);
               // other threads will stop when they see this flag
				pthread_mutex_lock(&info->death_lock);
				info->philo_died = 1;
				pthread_mutex_unlock(&info->death_lock);
				return (NULL);
			}
			i++;
		}

		if (info->number_of_rep > 0)
		{
			pthread_mutex_lock(&info->full_lock);
			if (info->philo_full == info->number_of_philo)
			{
				pthread_mutex_unlock(&info->full_lock);
				pthread_mutex_lock(&info->death_lock);
				info->philo_died = 1;
				pthread_mutex_unlock(&info->death_lock);
				return (NULL);
			}
			pthread_mutex_unlock(&info->full_lock);
		}
		usleep(1000);
	}
	return (NULL);
}
