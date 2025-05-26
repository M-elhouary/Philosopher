
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

void clean_mutex(t_info_of_each_philo *philos, t_philo_info info)
{
    int index;

    index = 0;
    while(index < info.number_of_philo)
    {
        pthread_mutex_destroy(&info.forks[index]);
        index++;
    }
    free(info.forks);
    free(philos);
}