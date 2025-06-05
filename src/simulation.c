/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 22:35:45 by mel-houa          #+#    #+#             */
/*   Updated: 2025/06/01 22:47:22 by mel-houa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo_header.h"

void ft_eat(t_info_of_each_philo *ph)
{

    long now;
    
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
}


int ft_sleep(t_info_of_each_philo *ph)
{
    long now;
    
    pthread_mutex_lock(&ph->genr_info->protect_meal);
    if (ph->genr_info->end == 1)
    {
        pthread_mutex_unlock(&ph->genr_info->protect_meal);
            return 1;
    }
    pthread_mutex_unlock(&ph->genr_info->protect_meal);
    now = get_current_time() - ph->genr_info->gen_time_start;
    printf("%ld %d is sleeping\n", now, ph->ID);
    usleep(ph->genr_info->time_to_sleep * 1000);
}
int  ft_think(t_info_of_each_philo *ph)
{
    long now;
    pthread_mutex_lock(&ph->genr_info->protect_meal);
    if (ph->genr_info->end == 1)
    {
        pthread_mutex_unlock(&ph->genr_info->protect_meal);
            return 1;
    }
    pthread_mutex_unlock(&ph->genr_info->protect_meal);
    now = get_current_time() - ph->genr_info->gen_time_start;
    printf("%ld %d is thinking\n", now, ph->ID);
    usleep(ph->genr_info->time_to_think * 1000);
}