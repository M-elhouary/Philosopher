/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 22:40:19 by mel-houa          #+#    #+#             */
/*   Updated: 2025/05/29 00:23:38 by mel-houa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo_header.h"


void *routine(void *arg)
{
    t_info_of_each_philo *ph = arg;
    long now;

    while (1)
    {
    pthread_mutex_lock(&ph->genr_info->death_lock);
    if (ph->genr_info->philo_died)
    {
        pthread_mutex_unlock(&ph->genr_info->death_lock);
        break;
    }
    pthread_mutex_unlock(&ph->genr_info->death_lock);

    if (ph->genr_info->number_of_rep > 0 &&
        ph->eat_count >= ph->genr_info->number_of_rep &&
        ph->marked_full == 0)
        break;
        if (ph->ID % 2 == 0)
        {
            // Even: right first
            pthread_mutex_lock(ph->right_fork);
            now = get_current_time() - ph->genr_info->gen_time_start;
            printf("%ld %d has taken a fork\n", now, ph->ID);

            pthread_mutex_lock(ph->left_fork);
            now = get_current_time() - ph->genr_info->gen_time_start;
            printf("%ld %d has taken a fork\n", now, ph->ID);
        }
        else
        {
            // Odd: left first
            pthread_mutex_lock(ph->left_fork);
            now = get_current_time() - ph->genr_info->gen_time_start;
            printf("%ld %d has taken a fork\n", now, ph->ID);

            pthread_mutex_lock(ph->right_fork);
            now = get_current_time() - ph->genr_info->gen_time_start;
            printf("%ld %d has taken a fork\n", now, ph->ID);
        }

        // Eat
        pthread_mutex_lock(&ph->meal_lock);
        ph->last_meal_time = get_current_time();    
        pthread_mutex_unlock(&ph->meal_lock);

        //check time 
        now = ph->last_meal_time - ph->genr_info->gen_time_start;
        printf("%ld %d is eating\n", now, ph->ID);
        usleep(ph->genr_info->time_to_eat * 1000);
        ph->eat_count++;
    if (ph->genr_info->number_of_rep > 0 &&
            ph->eat_count == ph->genr_info->number_of_rep)
        {
            pthread_mutex_lock(&ph->genr_info->full_lock);
            ph->genr_info->philo_full++;
            pthread_mutex_unlock(&ph->genr_info->full_lock);
        }


        pthread_mutex_unlock(ph->left_fork);
        pthread_mutex_unlock(ph->right_fork);

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
    create_fork(&info, philos);
    // get cuurent time
    info.gen_time_start = get_current_time();
    initial(&philos, &info);
    creat_join_th(philos, &info);
    //monitor(av);
    clean_mutex(philos, &info);
    
    return (0);
}
