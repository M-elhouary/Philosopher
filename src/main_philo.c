/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 22:40:19 by mel-houa          #+#    #+#             */
/*   Updated: 2025/05/31 02:08:53 by mel-houa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo_header.h"



void *routine(void *arg)
{
    t_info_of_each_philo *ph = arg;
    long now;

    while (1)
    {
        pthread_mutex_lock(&ph->genr_info->protect_meal);
        if (ph->genr_info->end == 1 )
        {
            pthread_mutex_unlock(&ph->genr_info->protect_meal);
                break;
        }
        pthread_mutex_unlock(&ph->genr_info->protect_meal);
        if(get_fork(ph))
            break;
        // Eat
        ph->last_meal_time = get_current_time();
        //check time 
        now = ph->last_meal_time - ph->genr_info->gen_time_start;
        printf("%ld %d is eating\n", now, ph->ID);
        usleep(ph->genr_info->time_to_eat * 1000);
        pthread_mutex_lock(&ph->genr_info->protect_meal);
        ph->eat_count++;
        if(ph->eat_count == ph->genr_info->number_of_rep
            && ph->genr_info->number_of_rep)
            {
                ph->genr_info->full_food++;
            }
        pthread_mutex_unlock(&ph->genr_info->protect_meal);


        // Sleep
        now = get_current_time() - ph->genr_info->gen_time_start;
        printf("%ld %d is sleeping\n", now, ph->ID);
        usleep(ph->genr_info->time_to_sleep * 1000);

        // Think   
        now = get_current_time() - ph->genr_info->gen_time_start;
        printf("%ld %d is thinking\n", now, ph->ID);
    }
    return (NULL);
}

int main(int ac, char **av)
{
    t_philo_info info;
    t_info_of_each_philo *philos;
    int count; 
    
    count = 0;
    
    if(is_valide_arg(ac, av) == 0)
    {
        write(2, "Error: INVALIDE ARGUMENT\n", 26);
        return (1);
    }
    fill_info_of_philo(ac, av, &info);
    if(pthread_mutex_init(&info.protect_meal, NULL) != 0)
    {
        write(2, "Mutex init failed\n", 18);
        return (1);
    }
    if(create_fork(&info, philos))
        return (1);
    if(initial(&philos, &info))
        return (1);
    if(creat_join_th(philos, &info))
        return (1);
    clean_mutex(philos, &info);
    
    return (0);
}
