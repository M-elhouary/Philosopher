/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 22:40:19 by mel-houa          #+#    #+#             */
/*   Updated: 2025/05/26 21:34:51 by mel-houa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo_header.h"





void *routine(void *arg)
{
    t_info_of_each_philo *ph = arg;
    long now;

    while (1)
    {
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
        ph->last_meal_time = get_current_time();
        //check time 
        now = ph->last_meal_time - ph->genr_info->gen_time_start;
        printf("%ld %d is eating\n", now, ph->ID);
        usleep(ph->genr_info->time_to_eat * 1000);

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
    info.gen_time_start = get_current_time();
    initial(&philos, &info);
    creat_join_th(philos, &info);
    clean_mutex(philos, &info);
    
    return (0);
}
