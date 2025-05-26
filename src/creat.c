#include "philo_header.h"



 int create_fork(t_philo_info *info, t_info_of_each_philo *philo)
{
    int count;
    
    count = 0;
    info->forks = malloc(sizeof(pthread_mutex_t) * info->number_of_philo);
    if(!info->forks)
        return(1);
    while(count < info->number_of_philo)
       if( pthread_mutex_init(&info->forks[count++], NULL) != 0)
       {
            clean_mutex(philo, info);  
            return 1;
       }
    return (0);
    
}




int creat_join_th(t_info_of_each_philo *philos, t_philo_info *info)
{
    int count;
    
    count = 0;
    info->gen_time_start = get_current_time();
    while(count < info->number_of_philo)
    {
        philos[count].last_meal_time = get_current_time();
        if(pthread_create(&philos[count].thr, NULL, routine, &philos[count]) != 0)
        {
                printf("pthread_create faild");
                return(1);
        }
            count++;
    }
    count = 0;
    while(count < info->number_of_philo)
    {
        pthread_join((philos)[count].thr, NULL);
            count++;
    }
    return (0);
}

