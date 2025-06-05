#include "philo_header.h"


void *monitor(void *arg)
{

    t_info_of_each_philo *ph;
    int i;
    long now;
    long time_stamp;
    
    ph =  (t_info_of_each_philo *) arg;
    while (1)
    {
        i = 0;
        while(i < ph[0].genr_info->number_of_philo)
        {
            now = get_current_time() ;
            if(now - ph[i].last_meal_time  > ph[i].genr_info->time_to_die)
            { 
                pthread_mutex_lock(&ph->genr_info->protect_meal);
                      ph->genr_info->end = 1;
                pthread_mutex_unlock(&ph->genr_info->protect_meal);
                time_stamp = get_current_time() - ph->genr_info->gen_time_start;
                printf("%ld %d die\n", time_stamp, ph[i].ID);
                return NULL;
            }
            i++;
        }
        if(ph->genr_info->number_of_rep > 0)
        {    
             if(ph->genr_info->full_food == ph->genr_info->number_of_philo)
             {
                 pthread_mutex_lock(&ph->genr_info->protect_meal);
                 ph->genr_info->end = 1;
                 pthread_mutex_unlock(&ph->genr_info->protect_meal);
                 return NULL;
             }
        }
        usleep(1000);
    }
    return NULL;
}