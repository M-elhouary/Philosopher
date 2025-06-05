/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 22:40:19 by mel-houa          #+#    #+#             */
/*   Updated: 2025/06/01 23:13:11 by mel-houa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

void *routine(void *arg)
{
    t_info_of_each_philo *ph = arg;
    long now;
    
    // if(ph->ID % 2 == 0)
    //     usleep(1000);
    while (1)
    {
        pthread_mutex_lock(&ph->genr_info->protect_meal);
        if (ph->genr_info->end == 1)
        {
            pthread_mutex_unlock(&ph->genr_info->protect_meal);
                break;
        }
        pthread_mutex_unlock(&ph->genr_info->protect_meal);
        if(get_fork(ph))
            break;
        // Eat
        ft_eat(ph);
        pthread_mutex_unlock(ph->left_fork);
        pthread_mutex_unlock(ph->right_fork);
        // Sleep
    
        ft_sleep(ph);
        // Think   
        ft_think(ph);
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
    return 0;
}
