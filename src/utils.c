
#include "philo_header.h"

long get_current_time()
{
    struct timeval tv;
    long second;
    long microsecond;
    long millisecond;

    gettimeofday(&tv, NULL);
    second = tv.tv_sec;
    microsecond = tv.tv_usec;
    millisecond = (second * 1000) + (microsecond / 1000);
    return (millisecond);
}

void clean_mutex(t_info_of_each_philo *philos, t_philo_info *info)
{
    int index;

    index = 0;
    while(index < info->number_of_philo)
    {
        pthread_mutex_destroy(&info->forks[index]);
        pthread_mutex_destroy(&philos[index].meal_lock);
        index++;
    }
    pthread_mutex_destroy(&info->full_lock);
    pthread_mutex_destroy(&info->death_lock);

    free(info->forks);
    free(philos);
}